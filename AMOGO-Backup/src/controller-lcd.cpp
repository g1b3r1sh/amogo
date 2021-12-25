#include "controller-lcd.h"

namespace controllerLCD
{
  void resetScreen(controller c)
  {
    c.Screen.clearScreen();
    c.Screen.setCursor(1, 1);
  }

  void displayValue(controller c, std::string name, int val)
  {
    c.Screen.print("%s: %d", name.c_str(), val);
    c.Screen.newLine();
  }

  void displayValue(controller c, std::string name, double val)
  {
    c.Screen.print("%s: %f", name.c_str(), val);
  }
}