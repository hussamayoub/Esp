/*done*/
#ifndef HEATER_H
#define HEATER_H

#include "HCHeater.h"
class Heater
{
private:
  HCHeater *hc;

public:
  Heater::Heater(HCHeater *HC);
  int GetTemp();  //return temprature
  //set heater I pass desired level and current water level because heater cant start if water is less than third
  void SetHeater(int targetTemp, double waterLevel);
};
#endif
