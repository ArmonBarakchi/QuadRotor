"""
cbf.py
------
Control Barrier Function (CBF) safety filter for quadrotor obstacle avoidance.

The CBF constraint is only enforced when the drone is at risk:
  - Inside or near the safety radius (h < h_threshold)
  - AND approaching the obstacle (h_dot_vel < 0)

This prevents the CBF from fighting the planner when the drone is safely
navigating toward a goal that happens to be in the general direction of
a distant obstacle.

The safety threshold is set generously (r + lookahead_margin) to give
the CBF enough time to act before the drone reaches the obstacle.
"""

import numpy as np
import cvxpy as cp


class CBF:
    """
    CBF safety filter for quadrotor with spherical obstacles.

    Args:
        mass            : drone mass (kg)
        f_max           : maximum total thrust magnitude (N)
        alpha           : class-K gain (0.5–3.0)
        safety_radius   : minimum allowed distance from obstacle center (m)
        lookahead_dist  : activate CBF this many meters before safety radius (m)
    """

    def __init__(self,
                 mass:           float,
                 f_max:          float = 0.6,
                 alpha:          float = 1.0,
                 safety_radius:  float = 0.30,
                 lookahead_dist: float = 0.5):

        self.m              = mass
        self.f_max          = f_max
        self.alpha          = alpha
        self.r              = safety_radius
        self.lookahead_dist = lookahead_dist
        self.obstacles      = []

    def set_obstacles(self, centers: list):
        self.obstacles = [np.array(c, dtype=float) for c in centers]

    def add_obstacle(self, center: np.ndarray):
        self.obstacles.append(np.array(center, dtype=float))

    def filter(self,
               pos:   np.ndarray,
               vel:   np.ndarray,
               F_nom: np.ndarray) -> tuple:
        """
        Apply CBF safety filter. Only modifies F when drone is close to
        and approaching an obstacle.

        Returns:
            F_safe : safe force vector (3,)
            active : indices of obstacles with active constraints
            h_vals : barrier values for each obstacle
        """
        if not self.obstacles:
            return F_nom.copy(), [], []

        F_nom = np.array(F_nom, dtype=float)
        F     = cp.Variable(3)

        constraints  = []
        h_vals       = []
        active       = []
        any_enforced = False

        # Threshold: enforce CBF when drone is within this distance of surface
        h_thresh = (self.r + self.lookahead_dist) ** 2

        for i, p_obs in enumerate(self.obstacles):
            diff      = pos - p_obs
            dist_sq   = float(diff @ diff)
            h         = dist_sq - self.r**2
            h_dot_vel = 2.0 * float(diff @ vel)

            h_vals.append(h)

            # Only enforce if close enough to matter
            # dist_sq < h_thresh means dist < r + lookahead_dist
            if dist_sq > h_thresh:
                continue

            # Enforce regardless of approach direction when inside safety radius
            # Enforce only when approaching when outside safety radius
            if h >= 0 and h_dot_vel >= 0:
                continue  # outside safety radius and moving away — no action needed

            any_enforced = True

            lhs = (2.0 / self.m) * cp.sum(cp.multiply(diff, F))
            rhs = float(-self.alpha * h - h_dot_vel)
            constraints.append(lhs >= rhs)

            active.append(i)

        if not any_enforced:
            return F_nom.copy(), [], h_vals

        constraints.append(F <=  self.f_max)
        constraints.append(F >= -self.f_max)

        problem = cp.Problem(cp.Minimize(cp.sum_squares(F - F_nom)),
                             constraints)

        try:
            problem.solve(solver=cp.OSQP,
                          warm_starting=True,
                          eps_abs=1e-5,
                          eps_rel=1e-5,
                          max_iter=10000,
                          verbose=False)

            if F.value is not None and problem.status in [
                    'optimal', 'optimal_inaccurate']:
                F_safe = np.array(F.value, dtype=float)
            else:
                nearest   = min(self.obstacles,
                                key=lambda p: np.linalg.norm(pos - p))
                direction = (pos - nearest) / (np.linalg.norm(pos - nearest) + 1e-9)
                F_safe    = direction * self.f_max * 0.8
                active    = list(range(len(self.obstacles)))

        except Exception:
            F_safe = F_nom.copy()

        return F_safe, active, h_vals

    def min_distance(self, pos: np.ndarray) -> float:
        """Distance from drone to nearest obstacle surface. Negative = inside."""
        if not self.obstacles:
            return float('inf')
        return float(min(np.linalg.norm(pos - p) - self.r
                         for p in self.obstacles))