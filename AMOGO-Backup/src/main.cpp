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

#include "main.h"

competition Competition;

void pre_auton(void)
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // Set brakeType of motors
  robot::setDriveStopping(brakeType::brake);
  tilter.setStopping(brakeType::hold);
  mogo.setStopping(brakeType::hold);

  // Zero motors
  robot::zeroMogoAndTilter();
}

// TODO: Create autonomous functions by meticulously testing and adjusting values
void autonomous(void)
{
  robot::setTilterForce(-20);
  wait(3000, timeUnits::msec);
  robot::setTilterForce(50);
  wait(1000, timeUnits::msec);
  robot::setTilterForce(0);
}

void usercontrol(void)
{
  if (TEST_AUTON)
  {
    autonomous();
  }

  bindings::initBindings();
  
  while (1)
  {
    /// Controller input processing
    controls::updateControls();

    wait(DELAY_TIME, msec);
  }
}

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