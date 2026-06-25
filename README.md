# SE3-Quad: Safe Autonomous Quadrotor Navigation in Unknown Environments

A full-stack quadrotor simulation system for safe waypoint navigation in unknown, obstacle-rich environments. The drone discovers obstacles online through simulated LiDAR, plans collision-free paths in real time, and enforces formal safety guarantees at every control step.

## Demo

```
mjpython fly_path_cbf.py --map forest
mjpython fly_path_cbf.py --map corridor
mjpython fly_path_cbf.py --map gates
mjpython fly_path_cbf.py --map spiral
```

---

## System Architecture

Four subsystems run in a layered pipeline at different rates:

```
500 Hz  │  IMU → UKF predict → Geometric controller → CBF filter → MuJoCo
 10 Hz  │  GPS → UKF update
 10 Hz  │  LiDAR scan → Obstacle map update
 10 Hz  │  RTAA* replan → Intermediate waypoint
```

| Component | Role | Guarantee |
|----------|------|-----------|
| **Multiplicative UKF** | State estimation on SE(3) | Position error ~0.15m at 10 Hz GPS |
| **LiDAR** | Online obstacle detection | Conservative radius inflation absorbs ~0.15m center error |
| **RTAA** | Real-time motion planning | Finds path using only local LiDAR map, no global map needed |
| **CBF** | Safety filter | Forward invariance of safe set at every timestep |

Physical parameters are read from the MuJoCo XML at runtime, obstacle positions come entirely from LiDAR, and paths are replanned online as the drone moves.

---

## Installation
 
### Requirements
 
- macOS (tested on Apple Silicon M-series)
- [Conda](https://docs.conda.io/en/latest/) or Python 3.11+
- MuJoCo 3.x — provides the `mjpython` launcher used to run all simulations
### Option A — Conda (recommended)
 
```bash
conda env create -f environment.yaml
conda activate quad
```
 
### Option B — pip
 
```bash
python -m venv .venv
source .venv/bin/activate
pip install -r requirements.txt
```
 
> **Note:** All simulations must be launched with `mjpython` (not `python`) 


### Repository Structure

```
QuadRotor/
├── src/
│   ├── Controllers/
│   │   ├── fly_path_cbf.py        # Main simulation entry point
│   │   ├── map_configs.py         # Map definitions
│   │   ├── cbf.py                 # Control Barrier Function safety filter
│   │   ├── rtaa_star.py           # RTAA* motion planner
│   │   ├── lidar.py               # Simulated LiDAR sensor
│   │   ├── ukf.py                 # Multiplicative UKF state estimator
│   │   ├── iekf.py                # Iterated EKF (comparison)
│   │   ├── ekf.py                 # EKF (comparison)
│   │   ├── ckf.py                 # Cubature KF (comparison)
│   │   └── geometric_controller.py
│   └── quadrotor_description/
│       └── models/
│           ├── quadrotor_cbf.xml       # Default map
│           ├── quadrotor_corridor.xml  # Narrow gap map
│           ├── quadrotor_forest.xml    # Dense pillar forest
│           ├── quadrotor_gates.xml     # Gate frames
│           └── quadrotor_spiral.xml    # Rising spiral
```

---

## Usage

### Run the full pipeline

```bash
cd src/Controllers
mjpython fly_path_cbf.py --map <map_name>
```

Available maps: `default`, `corridor`, `forest`, `gates`, `spiral`

### Flags

| Flag | Effect |
|------|--------|
| `--map <name>` | Select map (default: `default`) |
| `--no_cbf` | Disable CBF safety filter |
| `--no_rtaa` | Disable RTAA* planner (fly direct to goal) |
| `--no_ukf` | Use ground truth state instead of UKF |
| `--alpha <float>` | CBF class-K gain (default: 1.0) |
| `--lookahead <int>` | RTAA* nodes expanded per replan (default: 30) |

### Ablation examples

```bash
# Full system (recommended)
mjpython fly_path_cbf.py --map forest

# CBF disabled — drone will collide without safety filter
mjpython fly_path_cbf.py --map forest --no_cbf

# Planner disabled — drone gets stuck at local minima
mjpython fly_path_cbf.py --map forest --no_rtaa

# Ground truth state — bypasses UKF estimation
mjpython fly_path_cbf.py --map forest --no_ukf

# More aggressive CBF
mjpython fly_path_cbf.py --map corridor --alpha 2.0
```

---

## Maps

| Map | Obstacles | Goals | Challenge |
|-----|-----------|-------|-----------|
| **default** | 5 spheres in a cluster | 3 | Navigate around central cluster |
| **corridor** | 5 spheres forming two walls | 2 | Find and fly through the gap |
| **forest** | 6 pillars at varying heights | 3 | Weave through cluttered 3D space |
| **gates** | 4 gate posts + 1 overhead | 3 | Thread through narrow gate openings |
| **spiral** | 5 spheres in rising spiral | 3 | Climb while navigating laterally |

All obstacle positions are unknown to the drone at start and discovered entirely through LiDAR.

### Adding a new map

1. Create `src/quadrotor_description/models/quadrotor_<name>.xml`
   - Assign obstacle geoms to `group="1"` (detected by LiDAR)
   - Assign ground and drone geoms to `group="0"` (excluded from LiDAR)
2. Add an entry to `map_configs.py`:
```python
"mymap": {
    "desc": "Description of your map",
    "xml":  _xml("quadrotor_mymap.xml"),
    "goals": [
        np.array([x1, y1, z1]),
        np.array([x2, y2, z2]),
    ],
},
```
3. Run: `mjpython fly_path_cbf.py --map mymap`

---

## Key Parameters

| Parameter | Value | Description |
|-----------|-------|-------------|
| `CBF_SAFETY_RADIUS` | 0.30 m | Invisible safety boundary around each obstacle |
| `PLAN_RADIUS` | 0.27 m | RTAA* obstacle inflation (< CBF radius) |
| `OBSTACLE_VISUAL_RADIUS` | 0.15 m | Physical sphere radius in XML |
| `GPS_EVERY` | 50 steps | GPS update rate (~10 Hz) |
| `LIDAR_EVERY` | 50 steps | LiDAR scan rate (~10 Hz) |
| `REPLAN_EVERY` | 50 steps | RTAA* replan rate (~10 Hz) |
| `GOAL_THRESHOLD` | 0.25 m | Distance to count goal as reached |
| `d_act` | 0.50 m | CBF activation lookahead distance |


---

## Output

Each run prints a real-time table and a summary:

```
Map       : forest — Dense column forest — weave between pillars
Mode      : UKF + RTAA*(k=30) + CBF(α=1.0)
Physics   : mass=35.0g  gravity=9.81m/s²  dt=2.0ms  F_max=600mN
...
  ✓ Goal 1 reached at t=8.24s   ukf_err=0.143m   obs_known=4
  ✓ Goal 2 reached at t=19.71s  ukf_err=0.167m   obs_known=6
  ✓ Goal 3 reached at t=31.05s  ukf_err=0.151m   obs_known=5

══════════════════════════════════════════════════════════════════
  SUMMARY  —  FOREST  —  UKF + RTAA*(k=30) + CBF(α=1.0)
  Physics          : mass=35.0g  F_max=600mN  dt=2.0ms
  Goals reached    : 3/3
  UKF pos error    : mean=0.154m  max=0.391m
  Min obs distance : 0.042m (safety)  0.192m (surface)
  MuJoCo contacts  : 0
  CBF violations   : 12 steps (safety boundary, not collision)
  CBF activations  : 847/15500 (5.5%)
  Safety           : ✓ SAFE
  Navigation       : ✓ ALL GOALS REACHED
══════════════════════════════════════════════════════════════════
```



## Author

Armon Barakchi -- 2026
