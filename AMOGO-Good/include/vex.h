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
controller::axis* LEFT_DRIVE_AXIS;
controller::axis* RIGHT_DRIVE_AXIS;
controller::button* TILTER_IN_BUTTON;
controller::button* TILTER_OUT_BUTTON;
controller::button* MOGO_IN_BUTTON;
controller::button* MOGO_OUT_BUTTON;
controller::button* INVERSE_CONTROLS_BUTTON;
controller::button* SWITCH_DRIVE_BUTTON;

#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)

class toggler;