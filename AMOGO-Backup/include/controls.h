#include "vex.h"

extern controller::axis* FRONT_BACK_DRIVE_AXIS;
extern controller::axis* LEFT_RIGHT_DRIVE_AXIS;
extern controller::button* FRONT_DRIVE_BUTTON;
extern controller::button* BACK_DRIVE_BUTTON;
extern controller::button* LEFT_DRIVE_BUTTON;
extern controller::button* RIGHT_DRIVE_BUTTON;
extern controller::button* TILTER_IN_BUTTON;
extern controller::button* TILTER_OUT_BUTTON;
extern controller::button* MOGO_IN_BUTTON;
extern controller::button* MOGO_OUT_BUTTON;
extern controller::button* CONVEYOR_IN_BUTTON;
extern controller::button* CONVEYOR_OUT_BUTTON;
extern controller::button* INTAKE_IN_BUTTON;
extern controller::button* INTAKE_OUT_BUTTON;
extern controller::button* INVERSE_CONTROLS_BUTTON;
extern controller::button* SWITCH_DRIVE_BUTTON;

void initDriveControls();