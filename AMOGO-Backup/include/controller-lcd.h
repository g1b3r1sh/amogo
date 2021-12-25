#pragma once

#include "vex.h"

namespace controllerLCD
{
  void resetScreen(controller c);
  void displayValue(controller c, std::string name, int val);
  void displayValue(controller c, std::string name, double val);
}