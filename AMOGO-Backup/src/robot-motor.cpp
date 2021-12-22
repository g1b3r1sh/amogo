#include "robot-motor.h"

namespace robotMotor
{
  void setForce(motor& m, float percent) { m.spin(fwd, percent*MV_PCT_SCALE, voltageUnits::mV); }
  float getForce(motor& m) { return (float) m.voltage(voltageUnits::mV) / MV_PCT_SCALE; }
  
  void setVel(motor& m, int vel) { m.spin(fwd, vel, velocityUnits::rpm); }
  int getVel(motor& m) { return m.velocity(velocityUnits::rpm); }
  
  void setPos(motor& m, int pos, int vel) { m.startRotateTo(pos, rotationUnits::deg, vel, velocityUnits::pct); }
  int getPos(motor& m) { return m.rotation(rotationUnits::deg); }
}