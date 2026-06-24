"""
map_configs.py
--------------
All map definitions for the quadrotor CBF simulation.

Each map specifies:
    desc  : human-readable description
    xml   : path to MuJoCo XML (relative to quadrotor_description/models/)
    goals : list of global navigation goals in world frame

To add a new map:
    1. Create a new XML in quadrotor_description/models/
    2. Add an entry to MAPS below

Usage:
    from map_configs import get_map, list_maps
    cfg = get_map('forest')
"""

import os
import numpy as np

_HERE   = os.path.dirname(os.path.abspath(__file__))
_MODELS = os.path.normpath(
    os.path.join(_HERE, "../quadrotor_description/models"))


def _xml(filename):
    return os.path.join(_MODELS, filename)


MAPS = {
    "default": {
        "desc": "Central obstacle cluster — navigate around it",
        "xml":  _xml("quadrotor_cbf.xml"),
        "goals": [
            np.array([-0.7,  0.0, 1.00]),
            np.array([ 0.0,  0.0, 2.10]),
            np.array([ 0.6,  0.0, 1.00]),
        ],
    },
    "corridor": {
        "desc": "Two parallel walls with a gap — find the opening",
        "xml":  _xml("quadrotor_corridor.xml"),
        "goals": [
            np.array([-0.8,  0.0, 1.4]),
            np.array([ 0.6,  0.0, 1.0]),
        ],
    },
    "forest": {
        "desc": "Dense column forest — weave between pillars",
        "xml":  _xml("quadrotor_forest.xml"),
        "goals": [
            np.array([-0.8,  0.0, 1.3]),
            np.array([-0.3, -0.7, 1.5]),
            np.array([ 0.6,  0.0, 1.0]),
        ],
    },
    "gates": {
        "desc": "Gate frames — fly through each opening",
        "xml":  _xml("quadrotor_gates.xml"),
        "goals": [
            np.array([ 0.0,  0.0, 1.3]),
            np.array([ 0.0, -0.5, 1.5]),
            np.array([ 0.6,  0.0, 1.0]),
        ],
    },
    "spiral": {
        "desc": "Rising spiral of obstacles — climb while navigating",
        "xml":  _xml("quadrotor_spiral.xml"),
        "goals": [
            np.array([-0.1,  0.0, 2.1]),
            np.array([-0.6,  0.0, 1.2]),
            np.array([ 0.6,  0.0, 1.0]),
        ],
    },
}


def get_map(name: str) -> dict:
    if name not in MAPS:
        raise KeyError(f"Unknown map '{name}'. Available: {list_maps()}")
    return MAPS[name]


def list_maps() -> list:
    return list(MAPS.keys())


def print_maps():
    print("Available maps:")
    for name, cfg in MAPS.items():
        print(f"  {name:12s} — {cfg['desc']}")