import ctypes
import os
import pathlib


def _load_lib():
    """Find and load the compiled shlan shared library."""
    candidates = [
        pathlib.Path(__file__).parents[2] / "build" / "libshlan.so",
        pathlib.Path(__file__).parents[2] / "build" / "libshlan.dylib",
    ]
    for path in candidates:
        if path.exists():
            return ctypes.CDLL(str(path))
    raise RuntimeError(
        "libshlan not found — run: cmake -B build && cmake --build build"
    )


def before_all(context):
    lib = _load_lib()

    # shlan_sim_adapter_create() -> void*
    lib.shlan_sim_adapter_create.restype = ctypes.c_void_p
    lib.shlan_sim_adapter_create.argtypes = []

    # shlan_sim_adapter_destroy(void*)
    lib.shlan_sim_adapter_destroy.restype = None
    lib.shlan_sim_adapter_destroy.argtypes = [ctypes.c_void_p]

    # shlan_connect(void*) -> int
    lib.shlan_connect.restype = ctypes.c_int
    lib.shlan_connect.argtypes = [ctypes.c_void_p]

    # shlan_disconnect(void*)
    lib.shlan_disconnect.restype = None
    lib.shlan_disconnect.argtypes = [ctypes.c_void_p]

    # shlan_port_enable(void*, uint8_t) -> int
    lib.shlan_port_enable.restype = ctypes.c_int
    lib.shlan_port_enable.argtypes = [ctypes.c_void_p, ctypes.c_uint8]

    # shlan_port_disable(void*, uint8_t) -> int
    lib.shlan_port_disable.restype = ctypes.c_int
    lib.shlan_port_disable.argtypes = [ctypes.c_void_p, ctypes.c_uint8]

    context.lib = lib


def before_scenario(context, scenario):
    context.switch = context.lib.shlan_sim_adapter_create()
    context.lib.shlan_connect(context.switch)
    context.last_rc = 0


def after_scenario(context, scenario):
    context.lib.shlan_disconnect(context.switch)
    context.lib.shlan_sim_adapter_destroy(context.switch)
    context.switch = None
