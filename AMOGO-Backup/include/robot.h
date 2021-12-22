#pragma once

#include "vex.h"
#include "robot-motor.h"
#include "robot-config.h"

namespace robot
{
  void setDriveStopping(brakeType type);
  void setTankVoltage(int l, int r);
  void setTankRpm(int l, int r);

  void setMogoForce(int input);
  void setConveyorForce(int input);
  void setIntakeForce(int input);
  void setTilterForce(int input);

  void setMogoPos(int pos, int vel);
  void setTilterPos(int pos, int vel);

  void zeroMogoAndTilter();
}