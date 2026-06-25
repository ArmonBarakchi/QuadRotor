"""

Full-stack quadrotor: UKF state estimation + LiDAR obstacle detection
+ RTAA* motion planning + CBF safety filter.

Pipeline every timestep:
    MuJoCo physics  →  IMU/GPS simulation  →  UKF predict/update
    LiDAR scan      →  obstacle detection  →  RTAA* replan
    RTAA* waypoint  →  geometric ctrl      →  CBF filter  →  MuJoCo

Usage:
    mjpython fly_path_cbf.py                     # default map, full pipeline
    mjpython fly_path_cbf.py --map corridor
    mjpython fly_path_cbf.py --map forest
    mjpython fly_path_cbf.py --map gates
    mjpython fly_path_cbf.py --map spiral
    mjpython fly_path_cbf.py --no_cbf
    mjpython fly_path_cbf.py --no_rtaa
    mjpython fly_path_cbf.py --no_ukf
    mjpython fly_path_cbf.py --alpha 1.5
    mjpython fly_path_cbf.py --lookahead 30
"""

import argparse
import time
import numpy as np
import mujoco
import mujoco.viewer

from geometric_controller import GeometricController
from cbf import CBF
from rtaa_star import RTAAStar
from lidar import LiDAR
from ukf import UKF
from MAP_CONFIGS import get_map, list_maps


# ── Algorithm parameters  ───────────────────
INERTIA = np.diag([1.4e-5, 1.4e-5, 2.2e-5])

PRINT_EVERY    = 250
REPLAN_EVERY   = 100    # steps between RTAA* replans
LIDAR_EVERY    = 50    # steps between LiDAR scans
GPS_EVERY      = 50    # steps between GPS updates
GOAL_THRESHOLD = 0.15  # m — distance to count goal as reached
SIM_DURATION   = 60.0

# Sensor noises
GPS_NOISE   = 0.3
GYRO_NOISE  = 1e-3
ACCEL_NOISE = 2e-2
GYRO_BIAS   = np.array([ 0.005, -0.003,  0.002])
ACCEL_BIAS  = np.array([ 0.01,   0.02,  -0.01 ])

# Safety radii
CBF_SAFETY_RADIUS = 0.35
PLAN_RADIUS       = 0.30

DRONE_GEOMS          = {'hub','arm1','arm2','arm3','arm4',
                        'rotor1','rotor2','rotor3','rotor4'}
OBSTACLE_GEOM_PREFIX = 'obs'


# ── Helpers ──────────────
def get_ground_truth(data):
    pos   = data.qpos[0:3].copy()
    quat  = data.qpos[3:7].copy()
    vel   = data.qvel[0:3].copy()
    omega = data.qvel[3:6].copy()
    R     = np.zeros(9)
    mujoco.mju_quat2Mat(R, quat)
    return pos, vel, R.reshape(3, 3), omega, quat

def safe_goal(goal, obstacles, safety_r, margin=0.1):
    """
    If goal is inside safety radius + margin of any obstacle,
    project it to the nearest safe point on the obstacle's surface.
    """
    safe = goal.copy()
    for obs_center in obstacles:
        diff = safe - obs_center
        dist = np.linalg.norm(diff)
        min_dist = safety_r + margin
        if dist < min_dist:
            # Push goal to just outside safety boundary
            safe = obs_center + (diff / dist) * min_dist
    return safe

def simulate_imu(data):
    accel = data.sensordata[0:3] + ACCEL_BIAS + np.random.randn(3)*ACCEL_NOISE
    gyro  = data.sensordata[3:6] + GYRO_BIAS  + np.random.randn(3)*GYRO_NOISE
    return accel, gyro


def simulate_gps(pos):
    return pos + np.random.randn(3) * GPS_NOISE


def check_mujoco_contacts(model, data):
    hits = []
    for i in range(data.ncon):
        c  = data.contact[i]
        g1 = mujoco.mj_id2name(model, mujoco.mjtObj.mjOBJ_GEOM, c.geom1) or ''
        g2 = mujoco.mj_id2name(model, mujoco.mjtObj.mjOBJ_GEOM, c.geom2) or ''
        if ((g1 in DRONE_GEOMS or g2 in DRONE_GEOMS) and
                (g1.startswith(OBSTACLE_GEOM_PREFIX) or
                 g2.startswith(OBSTACLE_GEOM_PREFIX))):
            obs = g1 if g1.startswith(OBSTACLE_GEOM_PREFIX) else g2
            hits.append((obs, float(c.dist)))
    return hits

# Visualize goals as green spheres in the viewer
def add_goal_markers(viewer, goals, current_goal_idx):
    for i, goal in enumerate(goals):
        if i < current_goal_idx:
            rgba = [0.5, 0.5, 0.5, 0.4]   # grey — already reached
        elif i == current_goal_idx:
            rgba = [0.0, 1.0, 0.0, 0.9]   # bright green — current
        else:
            rgba = [0.0, 0.0, 1.0, 0.4]   # blue — future
        viewer.user_scn.ngeom += 1
        g = viewer.user_scn.geoms[viewer.user_scn.ngeom - 1]
        mujoco.mjv_initGeom(g, mujoco.mjtGeom.mjGEOM_SPHERE,
                            np.array([0.06, 0, 0]),   # size
                            goal,                      # position
                            np.eye(3).flatten(),       # rotation
                            np.array(rgba, dtype=np.float32))

# ── Main ────────────────────────────────────────────────────────────────────────

def main(map_name='default', use_cbf=True, use_rtaa=True, use_ukf=True,
         alpha=1.5, lookahead=15):

    cfg   = get_map(map_name)
    GOALS = cfg['goals']
    START = np.array([0.6, 0.0, 1.0])

    # ── Load MuJoCo model ───────────────
    model = mujoco.MjModel.from_xml_path(cfg['xml'])
    data  = mujoco.MjData(model)

    MASS    = float(model.body_mass[1:].sum())            # sum all non-world bodies
    GRAVITY = float(abs(model.opt.gravity[2]))             # z gravity magnitude
    SIM_DT  = float(model.opt.timestep)                   # physics timestep
    F_MAX   = float(model.actuator_ctrlrange[:, 1].sum()) # sum of actuator maxima

    mujoco.mj_resetData(model, data)
    body_id = mujoco.mj_name2id(model, mujoco.mjtObj.mjOBJ_BODY, "quadrotor")
    data.qpos[0:3] = START
    data.qpos[3]   = 1.0
    data.qpos[4:7] = 0.0
    mujoco.mj_forward(model, data)

    # ── Subsystems ───────

    #controller
    controller = GeometricController(mass=MASS, inertia=INERTIA, gravity=GRAVITY)
    controller.kp = 2.0
    controller.kv = 1.2

    #state estimation
    ukf = UKF(mass=MASS, gravity=GRAVITY)
    ukf.initialize(pos=START, vel=np.zeros(3),
                   quat=np.array([1., 0., 0., 0.]))

    #obstacle detection
    lidar = LiDAR(n_horizontal=72, n_vertical=9, fov_vertical=90.0,
                  max_range=2.0, safety_margin=0.20,
                  cluster_eps=0.35, min_hits=3)

    #safety filter
    cbf = CBF(mass=MASS, f_max=F_MAX, alpha=alpha,
              safety_radius=CBF_SAFETY_RADIUS,
              lookahead_dist=0.3)

    #motion planner
    planner = RTAAStar(grid_res=0.25, lookahead=lookahead,
                       bounds=((-1.5, 1.5), (-1.5, 1.5), (0.3, 2.3)),
                       plan_radius=PLAN_RADIUS)

    # ── Mode string for diagnostics──────────────────────────────────────────────────────────
    parts = []
    if use_ukf:  parts.append("UKF")
    if use_rtaa: parts.append(f"RTAA*(k={lookahead})")
    if use_cbf:  parts.append(f"CBF(α={alpha})")
    mode_str = " + ".join(parts) if parts else "ground-truth/direct"

    print(f"\nMap       : {map_name} — {cfg['desc']}")
    print(f"Mode      : {mode_str}")
    print(f"Physics   : mass={MASS*1000:.1f}g  gravity={GRAVITY:.2f}m/s²  "
          f"dt={SIM_DT*1000:.1f}ms  F_max={F_MAX*1000:.0f}mN")
    print(f"Goals     : {len(GOALS)}")
    for i, g in enumerate(GOALS):
        print(f"  goal{i+1}: {g}")
    print(f"LiDAR     : {lidar.n_rays} rays @ 2.0m range")
    print(f"Radii     : CBF={CBF_SAFETY_RADIUS}m  RTAA*={PLAN_RADIUS}m")
    print("-" * 85)
    print(f"{'t':>6}  {'est_pos':>22}  {'true_pos':>22}  "
          f"{'g':>2}  {'obs':>3}  status")
    print("-" * 85)

    # ── Tracking variables ───────
    step                    = 0
    start_wall              = time.time()
    goal_idx                = 0
    current_wp              = START.copy()
    known_obstacles         = []
    min_dist_ever           = float('inf')
    cbf_activations         = 0
    total_steps             = 0
    mujoco_collisions_total = 0
    cbf_violations_total    = 0
    first_collision_t       = None
    printed_collisions      = set()
    goal_arrival_times      = []
    ukf_errors              = []

    with mujoco.viewer.launch_passive(model, data) as viewer:
        viewer.cam.type        = mujoco.mjtCamera.mjCAMERA_TRACKING
        viewer.cam.trackbodyid = body_id
        viewer.cam.distance    = 2.8
        viewer.cam.elevation   = -20
        viewer.cam.azimuth     = 45

        while viewer.is_running():
            sim_time = data.time
            viewer.user_scn.ngeom = 0  # reset custom geoms each frame
            add_goal_markers(viewer, GOALS, goal_idx)
            if step % 2 == 0:
                viewer.sync()
            if SIM_DURATION and sim_time >= SIM_DURATION:
                print(f"\nTime limit t={sim_time:.1f}s")
                break
            if goal_idx >= len(GOALS):
                print(f"\nAll goals reached at t={sim_time:.1f}s")
                break

            # ── Ground truth used for comparison ───────────────────────
            pos_true, vel_true, R_true, omega_true, quat_true = \
                get_ground_truth(data)

            # ── IMU + UKF predict ────────────────────────────────────────────
            accel_meas, gyro_meas = simulate_imu(data)
            if use_ukf:
                ukf.predict(accel_meas, gyro_meas, dt=SIM_DT)

            # ── GPS update at 10 Hz ──────────────────────────────────────────
            if step % GPS_EVERY == 0:
                gps = simulate_gps(pos_true)
                if use_ukf:
                    ukf.update(gps)

            # ── State for control ────────────────────────────────────────────
            if use_ukf:
                pos_est, vel_est, R_est, omega_est = ukf.get_state()
            else:
                pos_est, vel_est, R_est, omega_est = \
                    pos_true, vel_true, R_true, omega_true

            ukf_errors.append(np.linalg.norm(pos_est - pos_true))

            # ── LiDAR scan at 10 Hz ──────────────────────────────────────────
            if step % LIDAR_EVERY == 0:
                detected = lidar.scan(model, data, pos_true, R_true, body_id)
                if detected:
                    known_obstacles = detected
                    centers = [c for c, r in known_obstacles]
                    cbf.set_obstacles(centers)
                    planner.set_obstacles(centers)

            # ── Goal arrival check ───────────────────────────────────────────
            dist_to_goal = np.linalg.norm(pos_est - GOALS[goal_idx])
            if dist_to_goal < GOAL_THRESHOLD and sim_time > 2.0:
                goal_arrival_times.append((goal_idx + 1, sim_time))
                print(f"\n Goal {goal_idx+1} reached at t={sim_time:.2f}s  "
                      f"ukf_err={ukf_errors[-1]:.3f}m  "
                      f"obs_known={len(known_obstacles)}")
                goal_idx += 1
                planner.reset_learning()
                current_wp = pos_est.copy()
                if goal_idx < len(GOALS):
                    print(f"  → Goal {goal_idx+1}: {GOALS[goal_idx]}")
                continue

            current_goal = GOALS[goal_idx]
            if known_obstacles:
                centers = [c for c, r in known_obstacles]
                target_safe = safe_goal(current_goal, centers,
                                        CBF_SAFETY_RADIUS, margin=0.10)
            else:
                target_safe = current_goal

            # ── RTAA* replan at 10 Hz ────────────────────────────────────────
            if use_rtaa and step % REPLAN_EVERY == 0:
                if known_obstacles:
                    current_wp = planner.next_waypoint(pos_est, target_safe)
                else:
                    current_wp = target_safe

            target = current_wp if use_rtaa else target_safe

            # ── Nominal force ────────────────────────────────────────────────
            ep    = pos_est - target
            ev    = vel_est
            F_nom = (-controller.kp * ep
                     - controller.kv * ev
                     + MASS * GRAVITY * np.array([0, 0, 1]))
            if np.linalg.norm(F_nom) > F_MAX:
                F_nom *= F_MAX / np.linalg.norm(F_nom)

            _, M, _ = controller.compute(
                pos=pos_est, vel=vel_est, R=R_est, omega=omega_est,
                pos_des=target, vel_des=np.zeros(3), acc_des=np.zeros(3))

            # ── CBF filter ───────────────────────────────────────────────────
            F_mod_norm     = 0.0
            cbf_active_now = False

            if use_cbf and known_obstacles:
                F_safe, active_obs, _ = cbf.filter(pos_est, vel_est, F_nom)
                F_mod_norm = float(np.linalg.norm(F_safe - F_nom))

                if active_obs:
                    cbf_active_now = True
                    cbf_activations += 1
                F_apply = F_safe
            else:
                F_apply = F_nom

            # ── Apply control to drone ─────────────────────────────────────────────────
            tau_world = R_true @ M
            data.xfrc_applied[body_id, 0] = float(F_apply[0])
            data.xfrc_applied[body_id, 1] = float(F_apply[1])
            data.xfrc_applied[body_id, 2] = float(F_apply[2])
            data.xfrc_applied[body_id, 3] = float(tau_world[0])
            data.xfrc_applied[body_id, 4] = float(tau_world[1])
            data.xfrc_applied[body_id, 5] = float(tau_world[2])
            data.ctrl[:] = 0.0

            mujoco.mj_step(model, data)
            if step % 2 == 0:
                viewer.sync()

            # ── Collision detection ──────────────────────────────────────────
            mujoco_hits = check_mujoco_contacts(model, data)
            if mujoco_hits:
                mujoco_collisions_total += len(mujoco_hits)
                if first_collision_t is None:
                    first_collision_t = sim_time
                for obs_name, depth in mujoco_hits:
                    key = f"{obs_name}_{sim_time:.1f}"
                    if key not in printed_collisions:
                        printed_collisions.add(key)
                        print(f"\n  !! CONTACT: {obs_name} "
                              f"pen={abs(depth)*1000:.1f}mm "
                              f"t={sim_time:.3f}s !!")

            min_dist = cbf.min_distance(pos_true)
            min_dist_ever = min(min_dist_ever, min_dist)
            if min_dist < 0:
                cbf_violations_total += 1
            total_steps += 1

            # ── Diagnostics ──────────────────────────────────────────────────
            if step % PRINT_EVERY == 0:
                if mujoco_hits:
                    status = "!! COLLISION !!"
                elif cbf_active_now:
                    status = f"⚠CBF({F_mod_norm*1000:.0f}mN)"
                else:
                    status = "safe"
                print(f"{sim_time:6.2f}s  "
                      f"[{pos_est[0]:+.2f},{pos_est[1]:+.2f},{pos_est[2]:+.2f}]  "
                      f"[{pos_true[0]:+.2f},{pos_true[1]:+.2f},{pos_true[2]:+.2f}]  "
                      f" g{goal_idx+1}  "
                      f"{len(known_obstacles):3d}  "
                      f"{status}")

            step += 1

    # ── Summary ─────────────────────────────────────────────────────────────────
    mean_err = float(np.mean(ukf_errors)) if ukf_errors else 0
    max_err  = float(np.max(ukf_errors))  if ukf_errors else 0

    print(f"\n{'═'*70}")
    print(f"  SUMMARY  —  {map_name.upper()}  —  {mode_str}")
    print(f"{'═'*70}")
    print(f"  Physics          : mass={MASS*1000:.1f}g  "
          f"F_max={F_MAX*1000:.0f}mN  dt={SIM_DT*1000:.1f}ms")
    print(f"  Goals reached    : {len(goal_arrival_times)}/{len(GOALS)}")
    for g_i, t in goal_arrival_times:
        print(f"    goal{g_i} at t={t:.2f}s")
    if use_ukf:
        print(f"  UKF pos error    : mean={mean_err:.3f}m  max={max_err:.3f}m")
    print(f"  Min obs distance : {min_dist_ever:.3f}m (safety)  "
          f"{min_dist_ever+0.15:.3f}m (surface)")
    print(f"  MuJoCo contacts  : {mujoco_collisions_total}")
    print(f"  CBF violations   : {cbf_violations_total} steps "
          f"(safety boundary, not collision)")
    if use_cbf:
        pct = 100 * cbf_activations / max(total_steps, 1)
        print(f"  CBF activations  : {cbf_activations}/{total_steps} ({pct:.1f}%)")
    if first_collision_t:
        print(f"  First collision  : t={first_collision_t:.3f}s")
    safe       = mujoco_collisions_total == 0
    goals_done = len(goal_arrival_times) == len(GOALS)
    print(f"  Safety           : {'SAFE' if safe else 'UNSAFE'}")
    print(f"  Navigation       : "
          f"{'ALL GOALS REACHED' if goals_done else f'{len(goal_arrival_times)}/{len(GOALS)}'}")
    print(f"{'═'*70}")


if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        description='Quadrotor UKF + LiDAR + RTAA* + CBF')
    parser.add_argument('--map',       type=str,   default='default',
                        choices=list_maps(),
                        help='Map to load (see map_configs.py)')
    parser.add_argument('--no_cbf',    action='store_true',
                        help='Disable CBF safety filter')
    parser.add_argument('--no_rtaa',   action='store_true',
                        help='Disable RTAA* planner (fly direct to goal)')
    parser.add_argument('--no_ukf',    action='store_true',
                        help='Disable UKF (use ground truth state)')
    parser.add_argument('--alpha',     type=float, default=1.0,
                        help='CBF class-K gain')
    parser.add_argument('--lookahead', type=int,   default=30,
                        help='RTAA* lookahead depth')
    args = parser.parse_args()
    main(map_name = args.map,
         use_cbf  = not args.no_cbf,
         use_rtaa = not args.no_rtaa,
         use_ukf  = not args.no_ukf,
         alpha    = args.alpha,
         lookahead= args.lookahead)