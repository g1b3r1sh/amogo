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
// lb                   motor         9               
// lf                   motor         10              
// rb                   motor         1               
// rf                   motor         13              
// conveyor             motor         12              
// intake               motor         11              
// mogo                 motor         18              
// tilter               motor         2               
// ---- END VEXCODE CONFIGURED DEVICES ----


// Note that all voltage input are in terms of percentage of max voltage of motors, 12V

#include "vex.h"
using namespace vex;

// A global instance of competition
competition Competition;


/// Global Variables
const int JOY_THRES     = 5;  // Threshold joystick value (-127 to 127) needed to pass in order to affect the drivetrain
const int DELAY_TIME    = 10; // Delay time for loops (ms)
const int MV_PCT_SCALE  = 120; // Scale to convert millivolts to percent
// Drive Train Control Constants
const int VOLTAGE_MIN   = 50;
const int VOLTAGE_MAX   = 100;
const int RPM_MIN       = 50;
const int RPM_MAX       = 100;

// Controls
void initControls()
{
  LEFT_DRIVE_AXIS          = &Controller1.Axis3;
  RIGHT_DRIVE_AXIS         = &Controller1.Axis2;
  TILTER_IN_BUTTON         = &Controller1.ButtonL1;
  TILTER_OUT_BUTTON        = &Controller1.ButtonL2;
  MOGO_IN_BUTTON           = &Controller1.ButtonR1;
  MOGO_OUT_BUTTON          = &Controller1.ButtonR2;
  INVERSE_CONTROLS_BUTTON  = &Controller1.ButtonB;
  SWITCH_DRIVE_BUTTON      = &Controller1.ButtonDown;
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

void setTankVoltage(int l, int r)
{
  lf.spin(fwd, l*MV_PCT_SCALE, voltageUnits::mV);
  lb.spin(fwd, l*MV_PCT_SCALE, voltageUnits::mV);
  rb.spin(fwd, r*MV_PCT_SCALE, voltageUnits::mV);
  rf.spin(fwd, r*MV_PCT_SCALE, voltageUnits::mV);
}

void setTankRpm(int l, int r)
{
  lf.spin(fwd, l, velocityUnits::rpm);
  lb.spin(fwd, l, velocityUnits::rpm);
  rb.spin(fwd, r, velocityUnits::rpm);
  rf.spin(fwd, r, velocityUnits::rpm);
}

// Set motor velocities
void setMotorVel    (motor& m, int input) { m.spin(fwd, input*MV_PCT_SCALE, voltageUnits::mV); }
void setMogoVel     (int input) { setMotorVel(mogo, input); }
void setConveyorVel (int input) { setMotorVel(conveyor, input); }
void setIntakeVel   (int input) { setMotorVel(intake, input); }
void setTilterVel   (int input) { setMotorVel(tilter, input); }

// Set motor positions
void setMotorPos  (motor& m, int pos, int vel) { m.startRotateTo(pos, rotationUnits::deg, vel, velocityUnits::pct); }
void setMogoPos   (int pos, int vel) { setMotorPos(mogo, pos, vel); }
void setTilterPos (int pos, int vel) { setMotorPos(tilter, pos, vel); }

// Get motor position in degrees
int getMotorPos(motor& m)
{
  return m.rotation(rotationUnits::deg);
}

// Get motor velocity in rpm
int getMotorVel(motor& m)
{
  return m.velocity(velocityUnits::rpm);
}

/// Reset Carriers
// Assumes positions of goal carriers (mogo and tilter) are at initial position, so that position becomes 0 for the motors
void zeroCarriers()
{
  mogo.resetPosition();
  tilter.resetPosition();
}



/// Internal Classes
class toggler
{
  public:
  toggler(void (*offFunc)(), void (*onFunc)(), bool startPos = false) : offFunc(offFunc), onFunc(onFunc), on(startPos) {}
  toggler(void (*toggleFunc)(), bool startPos = false) : offFunc(toggleFunc), onFunc(toggleFunc), on(startPos) {}
  toggler(bool startPos = false) : on(startPos) {}

  void toggle() {
    on = !on;
    run();
  }
  void run() { (on ? onFunc : offFunc)(); }
  bool isOn() { return on; }

  private:
  // off and on functions default as empty functions
  void (*offFunc)() = []() -> void {};
  void (*onFunc)() = []() -> void {};

  bool on;
};


/// Helper functions
// Map value from one scale to another
float map(float x, float fromLower, float fromUpper, float toLower, float toUpper)
{
  return (x - fromLower) * (toUpper - toLower) / (fromUpper - fromLower) + toLower;
}

// Retrieve sign of int, returns 0 if int is 0
int sign(int x)
{
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
  initControls();

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
void autonomous(void)
{
  // lol we don't have any
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
// Returns velocity of motor controlled by joystick axis
int calcJoystickVel(controller::axis* a)
{
  int pos = a->value();
  return abs(pos) > JOY_THRES ? sign(pos) * map(abs(pos), JOY_THRES, 127, VOLTAGE_MIN, VOLTAGE_MAX) : 0;
}

// Returns rpm of motor controlled by joytick axis
int calcJoystickRpm(controller::axis* a)
{
  int pos = a->value();
  return abs(pos) > JOY_THRES ? sign(pos) * map(abs(pos), JOY_THRES, 127, RPM_MIN, RPM_MAX) : 0;
}

// Moves motor unless it hits a threshold - assumes min and max create a valid range
void motorThresholdControl(motor& m, int min, int max, int vel)
{
  int motorPos = getMotorPos(m);
  if ((vel > 0 && motorPos <= max) || (vel < 0 && motorPos >= min))
  {
    setMotorVel(m, vel);
  }
  else
  {
    setMotorVel(m, 0);
  }
}

// Returns a direction multiplier based on if bumpers are pressed
int bumperDir(controller::button* fwdBumper, controller::button* bwdBumper)
{
  if (fwdBumper->pressing())
  {
    return 1;
  }
  else if (bwdBumper->pressing())
  {
    return -1;
  }
  else
  {
    return 0;
  }
}

void tilterControls()
{
  motorThresholdControl(tilter, 0, 180, 50 * bumperDir(TILTER_OUT_BUTTON, TILTER_IN_BUTTON));
}

void mogoControls()
{
  motorThresholdControl(mogo, 0, 1000, 100 * bumperDir(MOGO_OUT_BUTTON, MOGO_IN_BUTTON));
}


/// Drive Controls
// NOTE: Actually reversing the drive would require the motors to be reversed and the controls to be swapped
toggler mogoFirstDrive(true);
toggler voltageDrive;
void driveControls()
{
  if (voltageDrive.isOn())
  {
    if (mogoFirstDrive.isOn())
    {
      setTankVoltage(calcJoystickVel(LEFT_DRIVE_AXIS), calcJoystickVel(RIGHT_DRIVE_AXIS));
    }
    else
    {
      setTankVoltage(-calcJoystickVel(RIGHT_DRIVE_AXIS), -calcJoystickVel(LEFT_DRIVE_AXIS));
    }
  }
  else
  {
    if (mogoFirstDrive.isOn())
    {
      setTankRpm(calcJoystickRpm(LEFT_DRIVE_AXIS), calcJoystickRpm(RIGHT_DRIVE_AXIS));
    }
    else
    {
      setTankRpm(-calcJoystickRpm(RIGHT_DRIVE_AXIS), -calcJoystickRpm(LEFT_DRIVE_AXIS));
    }
  }
}


// Controller processing
// Controller Screen displays drive mode (mogo/intake first, voltage/RPM drive)
/* Example:
Mogo Volts Drive
*/
// If there is a difference in velocity of motors on a side, the faster one is the one that disconnected
void displayDriveStatus()
{
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1, 1);
  Controller1.Screen.print("%s, %s Drive", mogoFirstDrive.isOn() ? "Mogo" : "Intake", voltageDrive.isOn() ? "Volts" : "RPM");
}


void usercontrol(void)
{
  // User control setup (at least the ones not already encapsulated in functions)
  INVERSE_CONTROLS_BUTTON->pressed([]() -> void { mogoFirstDrive.toggle(); });
  SWITCH_DRIVE_BUTTON->pressed([]() -> void { voltageDrive.toggle(); });

  while (1)
  {
    /// Controller input processing
    driveControls();
    tilterControls();
    mogoControls();

    displayDriveStatus();

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