#include "controls.h"

namespace controls
{
  void updateControls()
  {
    driveControls();
    tilterControls();
    mogoControls();
  }
  

  /// Drive Controls
  void driveControls()
  {
    // Joypad controls override arcade controls
    arcadeControls();
    joypadControls();
  }
  
  // Arcade controls for drive (controlled by one joystick)
  void arcadeControls()
  {
    robot::setTankRpm(
      arcadeMapSpeed(bindings::FRONT_BACK_DRIVE_AXIS->value() + bindings::LEFT_RIGHT_DRIVE_AXIS->value() / 2),
      arcadeMapSpeed(bindings::FRONT_BACK_DRIVE_AXIS->value() - bindings::LEFT_RIGHT_DRIVE_AXIS->value() / 2)
    );
  }
  
  // Maps joystick values to drive speed values
  int arcadeMapSpeed(float value)
  {
    return (int) map(value, -JOYSTICK_MAX, JOYSTICK_MAX, -JOYSTICK_DRIVE_MAX_RPM, JOYSTICK_DRIVE_MAX_RPM);
  }
  
  // Joypad controls for drive (controlled by four buttons)
  void joypadControls()
  {
    if (bindings::FRONT_DRIVE_BUTTON->pressing())
    {
      robot::setTankRpm(JOYPAD_DRIVE_RPM, JOYPAD_DRIVE_RPM);
    }
    else if (bindings::BACK_DRIVE_BUTTON->pressing())
    {
      robot::setTankRpm(-JOYPAD_DRIVE_RPM, -JOYPAD_DRIVE_RPM);
    }
    else if (bindings::LEFT_DRIVE_BUTTON->pressing())
    {
      robot::setTankRpm(-JOYPAD_DRIVE_RPM, JOYPAD_DRIVE_RPM);
    }
    else if (bindings::RIGHT_DRIVE_BUTTON->pressing())
    {
      robot::setTankRpm(JOYPAD_DRIVE_RPM, -JOYPAD_DRIVE_RPM);
    }
  }

  
  /// Mogo and Tilter Control
  // Returns number representing direction between two buttons
  int directionButtons(controller::button* fwdButton, controller::button* bwdButton)
  {
    if (fwdButton->pressing())
    {
      return 1;
    }
    else if (bwdButton->pressing())
    {
      return -1;
    }
    else
    {
      return 0;
    }
  }

  // Controls for tilter
  void tilterControls()
  {
    robot::setTilterForce(TILTER_VOLTAGE * directionButtons(bindings::TILTER_OUT_BUTTON, bindings::TILTER_IN_BUTTON));
  }

  // Controls for mogo
  void mogoControls()
  {
    // Mogo with threshold
    /*int vel = MOGO_SPEED * directionButtons(MOGO_OUT_BUTTON, MOGO_IN_BUTTON);
    if (vel >= 0 || getMotorPos(mogo) > 0)
    {
      setMogoVel(vel);
    }
    else
    {
      setMogoVel(0);
    }*/
    // Mogo without threshold
    robot::setMogoForce(MOGO_VOLTAGE * directionButtons(bindings::MOGO_OUT_BUTTON, bindings::MOGO_IN_BUTTON));
  }
}