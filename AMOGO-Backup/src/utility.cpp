#include "utility.h"

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