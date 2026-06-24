"""
geometric_controller.py
-----------------------
Geometric controller on SE(3).

Key differences from previous version:
  - Returns R_des so caller can inspect it
  - Tilt limiter is simpler and more robust
  - Gains sized analytically for Crazyflie-class inertia
"""

import numpy as np


def hat(v):
    return np.array([
        [ 0,    -v[2],  v[1]],
        [ v[2],  0,    -v[0]],
        [-v[1],  v[0],  0   ]
    ])

def vee(S):
    return np.array([S[2,1], S[0,2], S[1,0]])


class GeometricController:

    def __init__(self, mass, inertia, gravity=9.81):
        self.m  = mass
        self.J  = inertia
        self.g  = gravity
        self.e3 = np.array([0.0, 0.0, 1.0])

        # Position gains
        self.kp = 0.8
        self.kv = 0.6

        # Attitude gains — sized for J ~ 1e-5 kg·m²
        # kR * eR must stay << max_moment = 0.054 * 0.15 = 0.0025 N·m
        # For eR ~ 0.1 rad: kR < 0.025
        self.kR = 0.010
        self.kW = 0.003

        # Hard tilt limit
        self.MAX_TILT = np.deg2rad(20)

    def compute(self, pos, vel, R, omega,
                pos_des, vel_des=None, acc_des=None,
                yaw_des=0.0, yaw_rate_des=0.0):

        if vel_des is None: vel_des = np.zeros(3)
        if acc_des is None: acc_des = np.zeros(3)

        # Position loop
        ep = pos - pos_des
        ev = vel - vel_des

        F_des = (-self.kp * ep
                 - self.kv * ev
                 + self.m * self.g * self.e3
                 + self.m * acc_des)

        # Clamp F_des magnitude to prevent wild attitude demands
        F_max = 4 * 0.15  # max total thrust
        F_norm = np.linalg.norm(F_des)
        if F_norm > F_max:
            F_des = F_des * (F_max / F_norm)

        # Thrust scalar
        b3 = R @ self.e3
        f  = float(F_des @ b3)
        f  = np.clip(f, 0.0, F_max)

        # Desired attitude
        R_des = self._desired_rotation(F_des, yaw_des)

        # Attitude error on SO(3)
        eR = vee(0.5 * (R_des.T @ R - R.T @ R_des))

        # Angular velocity error
        omega_des = R.T @ R_des @ np.array([0.0, 0.0, yaw_rate_des])
        eW = omega - omega_des

        # Moment — NOTE: drop gyro term, it's negligible at this scale
        # and adds noise amplification
        M = -self.kR * eR - self.kW * eW

        # Hard clamp moments to what rotors can actually deliver
        max_moment = 0.0025  # N·m
        M = np.clip(M, -max_moment, max_moment)

        return f, M, R_des

    def _desired_rotation(self, F_des, yaw_des):
        world_z = np.array([0.0, 0.0, 1.0])

        norm_F = np.linalg.norm(F_des)
        if norm_F < 1e-6:
            return np.eye(3)

        b3_des = F_des / norm_F

        # Tilt limiter
        cos_tilt = np.clip(np.dot(b3_des, world_z), 0.0, 1.0)
        tilt = np.arccos(cos_tilt)
        if tilt > self.MAX_TILT:
            t = np.tan(self.MAX_TILT)
            b3_des = np.array([b3_des[0], b3_des[1], 0.0])
            if np.linalg.norm(b3_des[:2]) > 1e-6:
                b3_des[:2] = b3_des[:2] / np.linalg.norm(b3_des[:2]) * t
            b3_des[2] = 1.0
            b3_des = b3_des / np.linalg.norm(b3_des)

        heading = np.array([np.cos(yaw_des), np.sin(yaw_des), 0.0])
        b2_des = np.cross(b3_des, heading)
        if np.linalg.norm(b2_des) < 1e-6:
            heading = np.array([0.0, 1.0, 0.0])
            b2_des = np.cross(b3_des, heading)
        b2_des = b2_des / np.linalg.norm(b2_des)
        b1_des = np.cross(b2_des, b3_des)

        return np.column_stack([b1_des, b2_des, b3_des])


def compute_attitude_error(R, R_des):
    return 0.5 * np.trace(np.eye(3) - R_des.T @ R)