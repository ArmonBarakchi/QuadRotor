"""
lidar.py
--------
Simulated LiDAR sensor for quadrotor using MuJoCo raycasting.

Uses mj_ray() with two key exclusions:
  1. bodyexclude = drone body_id  → drone never hits itself
  2. geomgroup mask [0,1,0,0,0]  → only casts against group 1 geoms
                                    (obstacle spheres, not ground/drone)

XML convention:
  group="0"  → ground plane, drone geoms (not raycasted)
  group="1"  → obstacle spheres (raycasted by LiDAR)

Hit points are clustered into obstacle estimates and radius-inflated
to absorb center estimation error (~0.15m typical).
"""

import numpy as np
import mujoco


class LiDAR:
    """
    Simulated spinning LiDAR sensor.

    Args:
        n_horizontal   : rays per vertical ring
        n_vertical     : number of vertical rings
        fov_vertical   : total vertical field of view (degrees)
        max_range      : maximum detection range (m)
        safety_margin  : added to detected radius for CBF/RTAA*
        cluster_eps    : DBSCAN clustering radius (m)
        min_hits       : minimum hits to form a valid cluster
    """

    def __init__(self,
                 n_horizontal:  int   = 72,
                 n_vertical:    int   = 9,
                 fov_vertical:  float = 90.0,
                 max_range:     float = 2.0,
                 safety_margin: float = 0.20,
                 cluster_eps:   float = 0.35,
                 min_hits:      int   = 3):

        self.max_range     = max_range
        self.safety_margin = safety_margin
        self.cluster_eps   = cluster_eps
        self.min_hits      = min_hits

        # Pre-compute ray directions in body frame
        self._rays = self._make_rays(n_horizontal, n_vertical, fov_vertical)

        # Geom group mask — only raycast group 1 (obstacles)
        # MuJoCo geomgroup is a length-6 uint8 array
        self._geomgroup = np.zeros(6, dtype=np.uint8)
        self._geomgroup[1] = 1   # enable group 1 only

        # Cache
        self.last_obstacles  = []
        self.last_hit_points = []

    @staticmethod
    def _make_rays(n_h, n_v, fov_v_deg):
        rays = []
        for v in np.linspace(-fov_v_deg/2, fov_v_deg/2, n_v) * np.pi/180:
            cv, sv = np.cos(v), np.sin(v)
            for h in np.linspace(0, 2*np.pi, n_h, endpoint=False):
                rays.append([cv*np.cos(h), cv*np.sin(h), sv])
        return np.array(rays, dtype=np.float64)

    @property
    def n_rays(self):
        return len(self._rays)

    def scan(self,
             model:     mujoco.MjModel,
             data:      mujoco.MjData,
             drone_pos: np.ndarray,
             drone_R:   np.ndarray,
             body_id:   int) -> list:
        """
        Perform one LiDAR scan.

        Args:
            model     : MuJoCo model
            data      : MuJoCo data
            drone_pos : drone world position (3,)
            drone_R   : drone rotation matrix (3,3)
            body_id   : drone body id — excluded from raycasting

        Returns:
            list of (center_estimate, safe_radius) tuples in world frame.
            Pass directly to CBF.set_obstacles() and RTAAStar.set_obstacles().
        """
        pnt     = np.array(drone_pos, dtype=np.float64)
        geom_id = np.array([-1], dtype=np.int32)
        hits    = []

        for ray_body in self._rays:
            ray_world = drone_R @ ray_body

            dist = mujoco.mj_ray(
                model, data,
                pnt, ray_world,
                self._geomgroup,   # only hit group-1 geoms (obstacles)
                1,                 # flg_static: include static geoms
                body_id,           # exclude drone body
                geom_id)

            if 0.05 < dist < self.max_range:
                hits.append(pnt + dist * ray_world)

        self.last_hit_points = hits

        if not hits:
            self.last_obstacles = []
            return []

        obstacles = self._cluster(np.array(hits), drone_pos)
        self.last_obstacles = obstacles
        return obstacles

    def _cluster(self, points: np.ndarray, drone_pos: np.ndarray) -> list:
        """
        Cluster hit points → obstacle (center, safe_radius) estimates.

        Center correction: hit points are on the near face of spheres,
        so we push the cluster centroid away from the drone by est_radius
        to get a better center estimate.

        Radius inflation: est_radius + safety_margin absorbs the remaining
        center estimation error so CBF/RTAA* stay safe.
        """
        n      = len(points)
        labels = -np.ones(n, dtype=int)
        cid    = 0

        for i in range(n):
            if labels[i] >= 0:
                continue
            dists     = np.linalg.norm(points - points[i], axis=1)
            neighbors = np.where(dists < self.cluster_eps)[0]
            if len(neighbors) < self.min_hits:
                continue
            labels[neighbors] = cid
            cid += 1

        obstacles = []
        for c in range(cid):
            cluster  = points[labels == c]
            centroid = cluster.mean(axis=0)

            # Estimated radius = max spread of hit points from centroid
            est_r = max(np.linalg.norm(cluster - centroid, axis=1).max(), 0.08)

            # Push centroid away from drone by est_r to correct for near-face bias
            to_obs = centroid - drone_pos
            d      = np.linalg.norm(to_obs)
            center = centroid + (to_obs / d) * est_r if d > 1e-6 else centroid

            # Conservative safe radius: estimated + margin
            safe_r = est_r + self.safety_margin

            obstacles.append((center, safe_r))

        return obstacles