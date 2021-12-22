#include "robot.h"

namespace robot
{
  // Sets drive type
  // Possible values are hold, coast, and brake
  void setDriveStopping(brakeType type)
  {
    lf.setStopping(type);
    lb.setStopping(type);
    rf.setStopping(type);
    rb.setStopping(type);
  }

  void setTankVoltage(int l, int r)
  {
    robotMotor::setForce(lf, l);
    robotMotor::setForce(lb, l);
    robotMotor::setForce(rf, r);
    robotMotor::setForce(rb, r);
  }

  // Set rpm of drive motors
  void setTankRpm(int l, int r)
  {
    robotMotor::setVel(lf, l);
    robotMotor::setVel(lb, l);
    robotMotor::setVel(rf, r);
    robotMotor::setVel(rb, r);
  }
  
  void setMogoForce     (int percent) { robotMotor::setForce(mogo, percent); }
  void setConveyorForce (int percent) { robotMotor::setForce(conveyor, percent); }
  void setIntakeForce   (int percent) { robotMotor::setForce(intake, percent); }
  void setTilterForce   (int percent) { robotMotor::setForce(tilter, percent); }
  
  void setMogoPos   (int pos, int vel) { robotMotor::setPos(mogo, pos, vel); }
  void setTilterPos (int pos, int vel) { robotMotor::setPos(tilter, pos, vel); }

  // Makes current position of motors equal to 0
  void zeroMogoAndTilter()
  {
    mogo.resetPosition();
    tilter.resetPosition();
  }
}