# SPDX-License-Identifier: Apache-2.0
from behave import given, when, then

# Every step checks the simulated switch's own port flags (context.ports, see
# environment.py) instead of repeating an operation and trusting its result.


@given("the switch is connected")
def step_switch_connected(context):
    # A new adapter already reads every port disabled, so start from every
    # port enabled: connecting must visibly reset each flag.
    ports = context.ports
    ports.set_all(ports.ENABLED)
    rc = context.lib.shlan_connect(context.switch)
    assert rc == 0, f"connecting returned {rc}, expected 0"
    ports.expect((ports.DISABLED,) * len(ports), "connecting")


def _set_port(context, operation, action, port_id, flag):
    """Call one port operation and check that it changed only that port."""
    ports = context.ports
    context.flags_before = ports.flags()
    context.last_rc = operation(context.switch, port_id)
    expected = list(context.flags_before)
    if port_id < len(ports):
        assert context.last_rc == 0, \
            f"{action} returned {context.last_rc}, expected 0"
        expected[port_id] = flag
    else:
        assert context.last_rc != 0, \
            f"{action} returned 0, but the simulated switch has no such port"
    ports.expect(expected, action)


def _enable(context, port_id):
    _set_port(context, context.lib.shlan_port_enable,
              f"enabling port {port_id}", port_id, context.ports.ENABLED)


def _port_state(context, port_id):
    assert port_id < len(context.ports), \
        f"the simulated switch has no port {port_id}"
    return context.ports.state(port_id)


@given("port {port_id:d} is enabled")
def step_port_already_enabled(context, port_id):
    # A precondition must hold, so it cannot name a port the switch lacks.
    assert port_id < len(context.ports), \
        f"the simulated switch has no port {port_id}"
    _enable(context, port_id)


@when("port {port_id:d} is enabled")
def step_enable_port(context, port_id):
    _enable(context, port_id)


@when("port {port_id:d} is disabled")
def step_disable_port(context, port_id):
    _set_port(context, context.lib.shlan_port_disable,
              f"disabling port {port_id}", port_id, context.ports.DISABLED)


@then("port {port_id:d} should be active")
def step_port_active(context, port_id):
    state = _port_state(context, port_id)
    assert state == "enabled", f"port {port_id} not active: it is {state}"


@then("port {port_id:d} should be inactive")
def step_port_inactive(context, port_id):
    state = _port_state(context, port_id)
    assert state == "disabled", f"port {port_id} not inactive: it is {state}"


@then("the operation should fail")
def step_operation_failed(context):
    assert context.last_rc != 0, "expected failure but operation succeeded"
    context.ports.expect(context.flags_before, "the failed operation")
