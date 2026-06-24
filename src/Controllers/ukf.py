"""
ukf.py
------
Multiplicative Unscented Kalman Filter (MUKF) for quadrotor state estimation.

Uses scipy.spatial.transform.Rotation for all SO(3) operations and
mujoco built-ins where applicable.

State vector:
    x = [p (3), v (3), q (4), b_gyro (3), b_accel (3)]  — 16 elements

Error state (sigma points):  δx ∈ ℝ¹⁵
    Attitude perturbations via rotation vector (exp map)

Sensors:
    IMU  — accelerometer + gyro at 500 Hz
    GPS  — position at 10 Hz
"""

import numpy as np
from scipy.spatial.transform import Rotation


# ══════════════════════════════════════════════════════════════════════════════
# Quaternion convention helpers
# scipy uses [x,y,z,w], we use [w,x,y,z] internally
# ══════════════════════════════════════════════════════════════════════════════

def to_scipy(q):
    """[w,x,y,z] → [x,y,z,w] for scipy."""
    return np.array([q[1], q[2], q[3], q[0]])

def from_scipy(q):
    """[x,y,z,w] → [w,x,y,z] for internal use."""
    return np.array([q[3], q[0], q[1], q[2]])

def quat_mult(p, q):
    """Multiply two quaternions [w,x,y,z]."""
    r = Rotation.from_quat(to_scipy(p)) * Rotation.from_quat(to_scipy(q))
    return from_scipy(r.as_quat())

def quat_inv(q):
    """Inverse of unit quaternion [w,x,y,z]."""
    return from_scipy(Rotation.from_quat(to_scipy(q)).inv().as_quat())

def quat_to_R(q):
    """Unit quaternion [w,x,y,z] → 3x3 rotation matrix."""
    return Rotation.from_quat(to_scipy(q)).as_matrix()

def R_to_quat(R):
    """3x3 rotation matrix → unit quaternion [w,x,y,z]."""
    return from_scipy(Rotation.from_matrix(R).as_quat())

def exp_map(v):
    """Rotation vector v ∈ ℝ³ → unit quaternion [w,x,y,z]."""
    return from_scipy(Rotation.from_rotvec(v).as_quat())

def log_map(q):
    """Unit quaternion [w,x,y,z] → rotation vector v ∈ ℝ³."""
    return Rotation.from_quat(to_scipy(q)).as_rotvec()


# ══════════════════════════════════════════════════════════════════════════════
# UKF
# ══════════════════════════════════════════════════════════════════════════════

class UKF:
    """
    Multiplicative UKF for quadrotor state estimation.
    Error state dimension n=15 (quaternion perturbations live in ℝ³).
    """

    def __init__(self, mass, gravity=9.81):
        self.m   = mass
        self.g   = gravity
        self.e3  = np.array([0.0, 0.0, 1.0])
        self._last_omega = np.zeros(3)

        # ── State ──────────────────────────────────────────────────────────
        self.p       = np.zeros(3)
        self.v       = np.zeros(3)
        self.q       = np.array([1.0, 0.0, 0.0, 0.0])   # identity [w,x,y,z]
        self.b_gyro  = np.zeros(3)
        self.b_accel = np.zeros(3)

        # ── Error state covariance P ∈ ℝ¹⁵ˣ¹⁵ ────────────────────────────
        self.n = 15
        self.P = np.diag([
            0.01, 0.01, 0.01,        # position    (m²)
            0.01, 0.01, 0.01,        # velocity    (m/s)²
            0.001, 0.001, 0.001,     # attitude    (rad²)
            1e-4, 1e-4, 1e-4,        # gyro bias   (rad/s)²
            1e-4, 1e-4, 1e-4,        # accel bias  (m/s²)²
        ])

        # ── Process noise Q ────────────────────────────────────────────────
        gyro_noise       = 1e-3
        accel_noise      = 2e-2
        gyro_bias_drift  = 1e-5
        accel_bias_drift = 1e-4

        self.Q = np.diag([
            0, 0, 0,
            accel_noise**2,      accel_noise**2,      accel_noise**2,
            gyro_noise**2,       gyro_noise**2,       gyro_noise**2,
            gyro_bias_drift**2,  gyro_bias_drift**2,  gyro_bias_drift**2,
            accel_bias_drift**2, accel_bias_drift**2, accel_bias_drift**2,
        ])

        # ── Measurement noise R ────────────────────────────────────────────
        gps_noise  = 0.3   # metres std dev
        self.R_gps = np.eye(3) * gps_noise**2

        # ── Sigma point parameters ─────────────────────────────────────────
        self.alpha = 1e-2
        self.beta  = 2.0
        self.kappa = 0.0
        self.lam   = self.alpha**2 * (self.n + self.kappa) - self.n

        self.Wm    = np.full(2*self.n + 1, 1.0 / (2*(self.n + self.lam)))
        self.Wc    = np.full(2*self.n + 1, 1.0 / (2*(self.n + self.lam)))
        self.Wm[0] = self.lam / (self.n + self.lam)
        self.Wc[0] = (self.lam / (self.n + self.lam)
                      + (1 - self.alpha**2 + self.beta))

    # ── Public: set initial state ─────────────────────────────────────────────
    def initialize(self, pos, vel, quat):
        self.p = pos.copy()
        self.v = vel.copy()
        self.q = quat / np.linalg.norm(quat)

    # ── Internal: generate sigma points ──────────────────────────────────────
    def _sigma_points(self):
        """Return list of 2n+1 state tuples (p, v, q, b_g, b_a)."""
        n   = self.n
        lam = self.lam

        try:
            S = np.linalg.cholesky((n + lam) * self.P)
        except np.linalg.LinAlgError:
            S = np.linalg.cholesky((n + lam) * (self.P + 1e-9*np.eye(n)))

        # Zero perturbation = current mean
        deltas = np.zeros((2*n+1, n))
        for i in range(n):
            deltas[i+1]   =  S[:, i]
            deltas[i+1+n] = -S[:, i]

        sigma = []
        for d in deltas:
            p_i  = self.p      + d[0:3]
            v_i  = self.v      + d[3:6]
            q_i  = quat_mult(self.q, exp_map(d[6:9]))
            q_i  = q_i / np.linalg.norm(q_i)
            bg_i = self.b_gyro  + d[9:12]
            ba_i = self.b_accel + d[12:15]
            sigma.append((p_i, v_i, q_i, bg_i, ba_i))

        return sigma

    # ── Internal: propagate one sigma point through dynamics ──────────────────
    def _propagate(self, state, accel_meas, gyro_meas, dt):
        p, v, q, b_g, b_a = state

        # Correct for estimated bias
        gyro_corr  = gyro_meas  - b_g
        accel_corr = accel_meas - b_a

        # Rotate accel to world frame, remove gravity
        R           = quat_to_R(q)
        accel_world = R @ accel_corr - self.g * self.e3

        # Integrate
        p_new = p + v * dt
        v_new = v + accel_world * dt

        # Attitude integration via exp map
        q_new = quat_mult(q, exp_map(gyro_corr * dt))
        q_new = q_new / np.linalg.norm(q_new)

        return (p_new, v_new, q_new, b_g.copy(), b_a.copy())

    # ── Internal: weighted mean of sigma points ───────────────────────────────
    def _weighted_mean(self, sigma_prop):
        Wm = self.Wm

        p_mean  = sum(Wm[i] * sigma_prop[i][0] for i in range(len(Wm)))
        v_mean  = sum(Wm[i] * sigma_prop[i][1] for i in range(len(Wm)))
        bg_mean = sum(Wm[i] * sigma_prop[i][3] for i in range(len(Wm)))
        ba_mean = sum(Wm[i] * sigma_prop[i][4] for i in range(len(Wm)))

        # Geodesic mean for quaternions
        q_mean = sigma_prop[0][2].copy()
        for _ in range(10):
            e_sum = np.zeros(3)
            for i, (_, _, q_i, _, _) in enumerate(sigma_prop):
                dq = quat_mult(quat_inv(q_mean), q_i)
                if dq[0] < 0: dq = -dq
                e_sum += Wm[i] * log_map(dq)
            q_mean = quat_mult(q_mean, exp_map(e_sum))
            q_mean = q_mean / np.linalg.norm(q_mean)
            if np.linalg.norm(e_sum) < 1e-10:
                break

        return p_mean, v_mean, q_mean, bg_mean, ba_mean

    # ── Internal: error state from sigma point to mean ────────────────────────
    def _error_state(self, state, p_m, v_m, q_m, bg_m, ba_m):
        p_i, v_i, q_i, bg_i, ba_i = state
        dq = quat_mult(quat_inv(q_m), q_i)
        if dq[0] < 0: dq = -dq
        return np.concatenate([
            p_i  - p_m,
            v_i  - v_m,
            log_map(dq),
            bg_i - bg_m,
            ba_i - ba_m,
        ])

    # ══════════════════════════════════════════════════════════════════════════
    # PUBLIC API
    # ══════════════════════════════════════════════════════════════════════════

    def predict(self, accel_meas, gyro_meas, dt):
        """
        IMU prediction step. Call every timestep.

        accel_meas : (3,) accelerometer in body frame (m/s²)
        gyro_meas  : (3,) gyroscope in body frame (rad/s)
        dt         : timestep (s)
        """
        # Store corrected omega for get_state()
        self._last_omega = gyro_meas - self.b_gyro

        # 1. Sigma points
        sigma = self._sigma_points()

        # 2. Propagate through dynamics
        sigma_prop = [self._propagate(s, accel_meas, gyro_meas, dt)
                      for s in sigma]

        # 3. Weighted mean
        p_m, v_m, q_m, bg_m, ba_m = self._weighted_mean(sigma_prop)

        # 4. Predicted covariance
        P_pred = self.Q * dt
        for i, sp in enumerate(sigma_prop):
            d = self._error_state(sp, p_m, v_m, q_m, bg_m, ba_m)
            P_pred += self.Wc[i] * np.outer(d, d)

        # 5. Store
        self.p       = p_m
        self.v       = v_m
        self.q       = q_m
        self.b_gyro  = bg_m
        self.b_accel = ba_m
        self.P       = P_pred

    def update(self, gps_pos):
        """
        GPS position update step. Call at GPS rate.

        gps_pos : (3,) noisy GPS position measurement (m)
        """
        n  = self.n
        Wm = self.Wm
        Wc = self.Wc

        # 1. Sigma points from predicted state
        sigma = self._sigma_points()

        # 2. Measurement function h(x) = p  (GPS measures position)
        gamma  = np.array([s[0] for s in sigma])        # (2n+1, 3)
        y_mean = sum(Wm[i] * gamma[i] for i in range(2*n+1))

        # 3. Innovation covariance S and cross-covariance Pxy
        S   = self.R_gps.copy()
        Pxy = np.zeros((n, 3))
        for i, sp in enumerate(sigma):
            dx = self._error_state(sp,
                                   self.p, self.v, self.q,
                                   self.b_gyro, self.b_accel)
            dy   = gamma[i] - y_mean
            S   += Wc[i] * np.outer(dy, dy)
            Pxy += Wc[i] * np.outer(dx, dy)

        # 4. Kalman gain
        K = Pxy @ np.linalg.inv(S)

        # 5. State update via error state
        dx = K @ (gps_pos - y_mean)

        self.p      += dx[0:3]
        self.v      += dx[3:6]
        self.q       = quat_mult(self.q, exp_map(dx[6:9]))
        self.q       = self.q / np.linalg.norm(self.q)
        self.b_gyro  += dx[9:12]
        self.b_accel += dx[12:15]

        # 6. Covariance update
        self.P = self.P - K @ S @ K.T
        self.P = 0.5 * (self.P + self.P.T)   # symmetrize

    def get_state(self):
        """
        Returns current state estimate.

        Returns:
            pos   : (3,)   estimated position (m)
            vel   : (3,)   estimated velocity (m/s)
            R     : (3,3)  estimated rotation matrix
            omega : (3,)   bias-corrected angular velocity (rad/s)
        """
        R = quat_to_R(self.q)
        return self.p.copy(), self.v.copy(), R, self._last_omega.copy()