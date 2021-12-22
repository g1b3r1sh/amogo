#pragma once

#include "vex.h"
#include "bindings.h"
#include "robot.h"

namespace controls
{
  // Hardware Constraints
  const int JOYSTICK_MAX              = 127; // Maximum value of joystick axis (negative is minimum value)
  
  // Control Constants
  const int TILTER_VOLTAGE            = 50; // % of max voltage
  const int MOGO_VOLTAGE              = 100; // % of max voltage
  const int JOYSTICK_DRIVE_MAX_RPM    = 127; // Max rpm
  const int JOYPAD_DRIVE_RPM          = 127; // Rpm to set motor to when in joypad drive

  void updateControls();

  void driveControls();
  void arcadeControls();
  int arcadeMapSpeed(float value);
  void joypadControls();

  int directionButtons(controller::button* fwdButton, controller::button* bwdButton);
  void tilterControls();
  void mogoControls();
}