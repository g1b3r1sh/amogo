/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Jess                                             */
/*    Created:      Thu Jul 15 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// lb                   motor         8               
// lf                   motor         3               
// rb                   motor         7               
// rf                   motor         6               
// conveyor             motor         12              
// intake               motor         9               
// mogo                 motor         2               
// tilter               motor         10              
// ---- END VEXCODE CONFIGURED DEVICES ----



#include "vex.h"
using namespace vex;

// A global instance of competition
competition Competition;


/// Global Variables
// Hardware Constants
const int JOYSTICK_MAX            = 127; // Maximum value of joystick axis (negative is minimum value)
// Control Constants
//const int JOY_THRES             = 5;  // Threshold joystick value (-127 to 127) needed to pass in order to affect the drivetrain
const int DELAY_TIME              = 10; // Delay time for loops (ms)
const int MV_PCT_SCALE            = 120; // Scale to convert mV to percent of max voltage of motors (12V)
const int TILTER_SPEED            = 50; // % of max voltage
const int MOGO_SPEED              = 100; // % of max voltage
// Drive Train Control Constants
const int JOYSTICK_DRIVE_MAX_RPM  = 127; // Max rpm
const int JOYPAD_DRIVE_RPM        = 127; // Rpm to set motor to when in joypad drive

// Control bindings (note: since this is executed at the start of the program, the Controller1 object doesn't exist yet,
//                         so map controls to joystick in initDriveControls())
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

/// Motor Movement Functions
// Sets drive type
// Possible values are hold, coast, and brake
void setDrive(brakeType type)
{
  lf.setStopping(type);
  lb.setStopping(type);
  rf.setStopping(type);
  rb.setStopping(type);
}

// Set voltage of drive motors
void setTankVoltage(int l, int r)
{
  lf.spin(fwd, l*MV_PCT_SCALE, voltageUnits::mV);
  lb.spin(fwd, l*MV_PCT_SCALE, voltageUnits::mV);
  rb.spin(fwd, r*MV_PCT_SCALE, voltageUnits::mV);
  rf.spin(fwd, r*MV_PCT_SCALE, voltageUnits::mV);
}

// Set rpm of drive motors
void setTankRpm(int l, int r)
{
  lf.spin(fwd, l, velocityUnits::rpm);
  lb.spin(fwd, l, velocityUnits::rpm);
  rb.spin(fwd, r, velocityUnits::rpm);
  rf.spin(fwd, r, velocityUnits::rpm);
}

// General function to set voltage
void setMotorVel    (motor& m, int input) { m.spin(fwd, input*MV_PCT_SCALE, voltageUnits::mV); }
// Set voltage of other motors
void setMogoVel     (int input) { setMotorVel(mogo, input); }
void setConveyorVel (int input) { setMotorVel(conveyor, input); }
void setIntakeVel   (int input) { setMotorVel(intake, input); }
void setTilterVel   (int input) { setMotorVel(tilter, input); }

// General function to set position
void setMotorPos  (motor& m, int pos, int vel) { m.startRotateTo(pos, rotationUnits::deg, vel, velocityUnits::pct); }
// Set position of other motors
void setMogoPos   (int pos, int vel) { setMotorPos(mogo, pos, vel); }
void setTilterPos (int pos, int vel) { setMotorPos(tilter, pos, vel); }

// Get current motor position
int getMotorPos   (motor& m) { return m.rotation(rotationUnits::deg); }
// Get current motor velocity
int getMotorVel   (motor& m) { return m.velocity(velocityUnits::rpm); }

/// Reset Carriers
// Makes current position of motors equal to 0
void zeroCarriers()
{
  mogo.resetPosition();
  tilter.resetPosition();
}


/// Helper functions
// Map value from one scale to another
float map(float x, float fromLower, float fromUpper, float toLower, float toUpper)
{
  return (x - fromLower) * (toUpper - toLower) / (fromUpper - fromLower) + toLower;
}

// Returns 1 if int is positive, -1 if int is negative, 0 if int is 0
int sign(int x)
{
  // This is 1*10^-6ms faster than if statements
  return (x > 0) - (x < 0);
}



/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void)
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // Set brakeType of motors
  setDrive(brakeType::brake);
  tilter.setStopping(brakeType::hold);
  mogo.setStopping(brakeType::hold);

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  zeroCarriers();
}



/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
// TODO: Create autonomous functions by meticulously testing and adjusting values
const bool TEST_AUTON = false; // If true, runs auton at start of drive phase (use for testing auton)
///
// Competition template function
///
void autonomous(void)
{
  //setTilterVel(-10);
  //wait(1800, timeUnits::msec);
  setTilterVel(-20);
  wait(3000, timeUnits::msec);
  setTilterVel(50);
  wait(1000, timeUnits::msec);
  setTilterVel(0);
}



/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

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
  setTilterVel(TILTER_SPEED * directionButtons(TILTER_OUT_BUTTON, TILTER_IN_BUTTON));
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
  setMogoVel(MOGO_SPEED * directionButtons(MOGO_OUT_BUTTON, MOGO_IN_BUTTON));
}

// Helper function for arcade controls - maps joystick values to drive speed values
int arcadeMapSpeed(float value)
{
  return (int) map(value, -JOYSTICK_MAX, JOYSTICK_MAX, -JOYSTICK_DRIVE_MAX_RPM, JOYSTICK_DRIVE_MAX_RPM);
}

// Arcade controls for drive (controlled by one joystick)
void arcadeControls()
{
  setTankRpm(
    arcadeMapSpeed(FRONT_BACK_DRIVE_AXIS->value() + LEFT_RIGHT_DRIVE_AXIS->value() / 2),
    arcadeMapSpeed(FRONT_BACK_DRIVE_AXIS->value() - LEFT_RIGHT_DRIVE_AXIS->value() / 2)
  );
}

// Joypad controls for drive (controlled by four buttons)
void joypadControls()
{
  if (FRONT_DRIVE_BUTTON->pressing())
  {
    setTankRpm(JOYPAD_DRIVE_RPM, JOYPAD_DRIVE_RPM);
  }
  else if (BACK_DRIVE_BUTTON->pressing())
  {
    setTankRpm(-JOYPAD_DRIVE_RPM, -JOYPAD_DRIVE_RPM);
  }
  else if (LEFT_DRIVE_BUTTON->pressing())
  {
    setTankRpm(-JOYPAD_DRIVE_RPM, JOYPAD_DRIVE_RPM);
  }
  else if (RIGHT_DRIVE_BUTTON->pressing())
  {
    setTankRpm(JOYPAD_DRIVE_RPM, -JOYPAD_DRIVE_RPM);
  }
}

/// Drive Controls
void driveControls()
{
  // Joypad controls override arcade controls
  arcadeControls();
  joypadControls();
}

///
// Competition template function
///
void usercontrol(void)
{
  if (TEST_AUTON)
  {
    autonomous();
  }

  initDriveControls();
  
  while (1)
  {
    /// Controller input processing
    driveControls();
    tilterControls();
    mogoControls();

    wait(DELAY_TIME, msec);
  }
}



//
// Main will set up the competition functions and callbacks.
//
int main()
{
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true)
  {
    wait(100, msec);
  }
}