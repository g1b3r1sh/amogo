/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       vex.h                                                     */
/*    Author:       Vex Robotics                                              */
/*    Created:      1 Feb 2019                                                */
/*    Description:  Default header for V5 projects                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
//
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "v5.h"
#include "v5_vcs.h"

#include "robot-config.h"

// Control aliases
/*
extern controller::axis* FRONT_BACK_DRIVE_AXIS;
extern controller::axis* LEFT_RIGHT_DRIVE_AXIS;
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
*/

#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)

class toggler;