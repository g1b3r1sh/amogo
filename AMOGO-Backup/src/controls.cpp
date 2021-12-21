#include "controls.h"
using namespace vex;

controller::axis* FRONT_BACK_DRIVE_AXIS;
controller::axis* LEFT_RIGHT_DRIVE_AXIS;
controller::button* FRONT_DRIVE_BUTTON;
controller::button* BACK_DRIVE_BUTTON;
controller::button* LEFT_DRIVE_BUTTON;
controller::button* RIGHT_DRIVE_BUTTON;
controller::button* TILTER_IN_BUTTON;
controller::button* TILTER_OUT_BUTTON;
controller::button* MOGO_IN_BUTTON;
controller::button* MOGO_OUT_BUTTON;
controller::button* CONVEYOR_IN_BUTTON;
controller::button* CONVEYOR_OUT_BUTTON;
controller::button* INTAKE_IN_BUTTON;
controller::button* INTAKE_OUT_BUTTON;
controller::button* INVERSE_CONTROLS_BUTTON;
controller::button* SWITCH_DRIVE_BUTTON;

// Bind bindings to controller
void initDriveControls()
{
  FRONT_BACK_DRIVE_AXIS    = &Controller1.Axis3;
  LEFT_RIGHT_DRIVE_AXIS    = &Controller1.Axis4;
  FRONT_DRIVE_BUTTON       = &Controller1.ButtonUp; 
  BACK_DRIVE_BUTTON        = &Controller1.ButtonDown;
  LEFT_DRIVE_BUTTON        = &Controller1.ButtonLeft;
  RIGHT_DRIVE_BUTTON       = &Controller1.ButtonRight;
  TILTER_IN_BUTTON         = &Controller1.ButtonX;
  TILTER_OUT_BUTTON        = &Controller1.ButtonA;
  MOGO_IN_BUTTON           = &Controller1.ButtonR1;
  MOGO_OUT_BUTTON          = &Controller1.ButtonR2;
}