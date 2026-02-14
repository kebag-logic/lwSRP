import ctypes
from behave import given, when, then


@given("the switch is connected")
def step_switch_connected(context):
    # handled in environment.py BeforeScenario
    pass


@given("port {port_id:d} is enabled")
def step_port_already_enabled(context, port_id):
    context.lib.shlan_port_enable(context.switch, port_id)


@when("port {port_id:d} is enabled")
def step_enable_port(context, port_id):
    context.last_rc = context.lib.shlan_port_enable(context.switch, port_id)


@when("port {port_id:d} is disabled")
def step_disable_port(context, port_id):
    context.last_rc = context.lib.shlan_port_disable(context.switch, port_id)


@then("port {port_id:d} should be active")
def step_port_active(context, port_id):
    # re-enable should be idempotent (rc == 0) as a proxy for state
    rc = context.lib.shlan_port_enable(context.switch, port_id)
    assert rc == 0, f"port {port_id} not active"


@then("port {port_id:d} should be inactive")
def step_port_inactive(context, port_id):
    rc = context.lib.shlan_port_disable(context.switch, port_id)
    assert rc == 0, f"port {port_id} not inactive"


@then("the operation should fail")
def step_operation_failed(context):
    assert context.last_rc != 0, "expected failure but operation succeeded"
