Feature: Switch port management

  Background:
    Given the switch is connected

  Scenario: Enable a port
    When port 0 is enabled
    Then port 0 should be active

  Scenario: Disable a port
    Given port 0 is enabled
    When port 0 is disabled
    Then port 0 should be inactive

  Scenario: Reject an out-of-range port
    When port 255 is enabled
    Then the operation should fail
