"""
rtaa_star.py
------------
Real-Time Adaptive A* (RTAA*) — optimized for real-time quadrotor use.

Performance optimizations:
  - 6-connected grid (vs 26) — 4x fewer neighbors, sufficient for 3D nav
  - Obstacle check in grid coords (precomputed integer radii)
  - Flat dict for heuristics (no object overhead)
  - Replan interval tunable — default every 50 steps (~10Hz at 500Hz sim)

LiDAR-ready: call set_obstacles() anytime to update the known obstacle map.

Reference:
    Koenig & Likhachev, "Real-time adaptive A*", AAMAS 2006.
"""

import numpy as np
import heapq


class RTAAStar:

    def __init__(self,
                 grid_res:    float = 0.10,
                 lookahead:   int   = 15,
                 bounds:      tuple = ((-1.5, 1.5), (-1.5, 1.5), (0.3, 2.5)),
                 plan_radius: float = 0.30):

        self.res         = grid_res
        self.k           = lookahead
        self.bounds      = bounds
        self.plan_radius = plan_radius
        self.h_table     = {}

        # Grid dimensions
        self.nx = int(round((bounds[0][1] - bounds[0][0]) / grid_res)) + 1
        self.ny = int(round((bounds[1][1] - bounds[1][0]) / grid_res)) + 1
        self.nz = int(round((bounds[2][1] - bounds[2][0]) / grid_res)) + 1

        # 6-connected moves: ±x, ±y, ±z only
        self._moves = [(1,0,0),((-1,0,0)),(0,1,0),(0,-1,0),(0,0,1),(0,0,-1)]

        # Obstacles stored as grid coords + integer radius
        self._obs_grid = []   # list of (gx, gy, gz, r_cells_sq)
        self._set_called = False

    def set_obstacles(self, centers: list):
        """Set obstacles from world-space centers. Precomputes grid coords."""
        r_cells = self.plan_radius / self.res
        r_sq    = r_cells ** 2
        self._obs_grid = []
        for c in centers:
            gx = int(round((c[0] - self.bounds[0][0]) / self.res))
            gy = int(round((c[1] - self.bounds[1][0]) / self.res))
            gz = int(round((c[2] - self.bounds[2][0]) / self.res))
            self._obs_grid.append((gx, gy, gz, r_sq))
        self._set_called = True

    def reset_learning(self):
        self.h_table.clear()

    def _w2g(self, pos):
        return (int(round((pos[0] - self.bounds[0][0]) / self.res)),
                int(round((pos[1] - self.bounds[1][0]) / self.res)),
                int(round((pos[2] - self.bounds[2][0]) / self.res)))

    def _g2w(self, node):
        return np.array([self.bounds[i][0] + node[i] * self.res
                         for i in range(3)])

    def _valid(self, x, y, z):
        if not (0 <= x < self.nx and 0 <= y < self.ny and 0 <= z < self.nz):
            return False
        for gx, gy, gz, r_sq in self._obs_grid:
            dx = x - gx; dy = y - gy; dz = z - gz
            if dx*dx + dy*dy + dz*dz <= r_sq:
                return False
        return True

    def _h(self, node, goal):
        """Euclidean heuristic, overridden by learned values."""
        dx = (node[0]-goal[0])*self.res
        dy = (node[1]-goal[1])*self.res
        dz = (node[2]-goal[2])*self.res
        h_euc = (dx*dx + dy*dy + dz*dz) ** 0.5
        return max(h_euc, self.h_table.get(node, 0.0))

    def next_waypoint(self, current_pos: np.ndarray,
                      goal_pos: np.ndarray) -> np.ndarray:
        """
        Run one RTAA* iteration. Returns next intermediate waypoint.
        Call this every REPLAN_EVERY simulation steps.
        """
        start = self._w2g(current_pos)
        goal  = self._w2g(goal_pos)

        if start == goal:
            return goal_pos.copy()

        # Escape if start is inside obstacle
        if not self._valid(*start):
            best, best_h = start, float('inf')
            for dx, dy, dz in self._moves:
                nb = (start[0]+dx, start[1]+dy, start[2]+dz)
                if self._valid(*nb):
                    h = self._h(nb, goal)
                    if h < best_h:
                        best_h = h
                        best   = nb
            start = best

        # Limited A* search
        open_heap = []
        came_from = {}
        g_score   = {start: 0.0}
        closed    = set()
        counter   = 0

        heapq.heappush(open_heap, (self._h(start, goal), counter, start))

        expanded = 0
        while open_heap and expanded < self.k:
            _, _, cur = heapq.heappop(open_heap)
            if cur in closed:
                continue
            closed.add(cur)
            if cur == goal:
                break
            expanded += 1
            for dx, dy, dz in self._moves:
                nx_, ny_, nz_ = cur[0]+dx, cur[1]+dy, cur[2]+dz
                if not self._valid(nx_, ny_, nz_):
                    continue
                nb    = (nx_, ny_, nz_)
                g_new = g_score[cur] + self.res
                if g_new < g_score.get(nb, float('inf')):
                    g_score[nb]   = g_new
                    came_from[nb] = cur
                    counter      += 1
                    heapq.heappush(open_heap,
                                   (g_new + self._h(nb, goal), counter, nb))

        # RTAA* learning: update h(start) to prevent revisiting
        if open_heap:
            min_f = open_heap[0][0]
            new_h = min_f - g_score.get(start, 0.0)
            if new_h > self.h_table.get(start, 0.0):
                self.h_table[start] = new_h

        # Trace one step from start
        if goal in came_from or goal == start:
            end = goal
        else:
            end = min(closed, key=lambda n: self._h(n, goal))

        node = end
        while node in came_from and came_from[node] != start:
            node = came_from[node]

        return self._g2w(node if node in came_from else end)

    def path_to_goal(self, start_pos, goal_pos, max_steps=300):
        """Simulate full RTAA* execution. For visualization/debugging."""
        path = [start_pos.copy()]
        pos  = start_pos.copy()
        self.reset_learning()
        for _ in range(max_steps):
            if np.linalg.norm(pos - goal_pos) < self.res * 1.5:
                path.append(goal_pos.copy())
                break
            pos = self.next_waypoint(pos, goal_pos)
            path.append(pos.copy())
        return path