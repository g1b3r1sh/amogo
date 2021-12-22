#pragma once

#include "vex.h"

namespace robotMotor
{
  static const int MV_PCT_SCALE = 120; // Scale to convert mV to percent of max voltage of motors (12V)
  
  // Set percent velocity of motor
  void setForce(motor& m, float percent);
  float getForce(motor& m);

  // Set rpm of motor
  void setVel(motor& m, int vel);
  int getVel(motor& m);

  void setPos(motor& m, int pos, int vel);
  int getPos(motor& m);
}