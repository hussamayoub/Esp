/*done*/
#ifndef WATER_H
#define WATER_H

#include "HCWater.h"

class Water
{
private:
  HCWater *hc;

public:
  Water(HCWater *HC);               // constructor
  int SetDrain(double targetLevel); //opens the water intake untill it reaches target level
  int SetSink(int val);             //Sinks the water untill tank is empty
  double GetWaterLevel();           //current water level
  int GetWaterPressur();            //water pressur state
};
#endif
