# SPDX-License-Identifier: Apache-2.0
import ctypes
import os
import pathlib
import re

SIM_ADAPTER = pathlib.Path(__file__).parents[2] / "src" / "modules" / "sim_adapter.c"


class _Switch(ctypes.Structure):
    # struct shlan_switch in src/include/shish_lan/switch.h
    _fields_ = [("ops", ctypes.c_void_p), ("priv", ctypes.c_void_p)]


def _sim_port_count():
    """Return SIM_MAX_PORTS while struct sim_priv holds only the port flags."""
    text = SIM_ADAPTER.read_text()
    count = re.search(r"^#define SIM_MAX_PORTS (\d+)$", text, re.MULTILINE)
    layout = re.search(
        r"^struct sim_priv \{\n\s*int port_state\[SIM_MAX_PORTS\];[^\n]*\n\};$",
        text, re.MULTILINE)
    assert count and layout, \
        f"struct sim_priv in {SIM_ADAPTER.name} no longer matches the port flag reader"
    return int(count.group(1))


def _span(ports):
    if len(ports) == 1:
        return f"port {ports[0]}"
    if ports[-1] - ports[0] + 1 == len(ports):
        return f"ports {ports[0]}-{ports[-1]}"
    return "ports " + ", ".join(map(str, ports))


class SimulatedPorts:
    """Read the simulated switch's own port flags, never through a binding."""

    DISABLED = 0
    ENABLED = 1
    _NAMES = {DISABLED: "disabled", ENABLED: "enabled"}

    def __init__(self, switch, count):
        handle = _Switch.from_address(switch)
        self._flags = (ctypes.c_int * count).from_address(handle.priv)

    def __len__(self):
        return len(self._flags)

    def flags(self):
        return tuple(self._flags)

    def _name(self, flag):
        return self._NAMES.get(flag, f"flagged {flag}")

    def state(self, port_id):
        return self._name(self._flags[port_id])

    def set_all(self, flag):
        for port_id in range(len(self._flags)):
            self._flags[port_id] = flag

    def expect(self, expected, action):
        """Fail naming each port whose flag differs from the expected flags."""
        wrong = {}
        for port_id, (flag, want) in enumerate(zip(self.flags(), expected)):
            if flag != want:
                wrong.setdefault((flag, want), []).append(port_id)
        assert not wrong, f"after {action}: " + "; ".join(
            f"{_span(ports)} {self._name(flag)}, expected {self._name(want)}"
            for (flag, want), ports in wrong.items()
        )


def _load_lib():
    """Find and load the compiled shlan shared library."""
    library = os.environ.get("SHLAN_LIBRARY")
    if library:
        return ctypes.CDLL(library)
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

    # Keep the established scenario bindings while the public operations
    # also provide exported entry points for foreign-function callers.
    for name, restype, argtypes in (
        ("connect", ctypes.c_int, [ctypes.c_void_p]),
        ("disconnect", None, [ctypes.c_void_p]),
        ("port_enable", ctypes.c_int, [ctypes.c_void_p, ctypes.c_uint8]),
        ("port_disable", ctypes.c_int, [ctypes.c_void_p, ctypes.c_uint8]),
    ):
        binding = getattr(lib, f"shlan_test_{name}")
        binding.restype = restype
        binding.argtypes = argtypes
        setattr(lib, f"shlan_{name}", binding)

    context.lib = lib
    context.port_count = _sim_port_count()


def before_scenario(context, scenario):
    # The Background step connects, so that it can check the connection.
    context.switch = context.lib.shlan_sim_adapter_create()
    assert context.switch, "the simulation adapter was not created"
    context.ports = SimulatedPorts(context.switch, context.port_count)
    context.last_rc = 0


def after_scenario(context, scenario):
    if not context.switch:
        return
    flags = context.ports.flags()
    context.lib.shlan_disconnect(context.switch)
    try:
        # The simulation's disconnect leaves every port flag as it was.
        context.ports.expect(flags, "disconnecting")
    finally:
        context.lib.shlan_sim_adapter_destroy(context.switch)
        context.switch = None
