/*done*/
#define waterPressurError -1
#include "Water.h"

Water::Water(HCWater *HC)
{
  this->hc = HC;
}

int Water::SetDrain(double targetLevel)
{
  if (targetLevel == 0) // if target level is 0
  {
    hc->SetDrain(0); // turn drainning off
    return 1;        // return done
  }
  if (hc->GetWaterPressur()) //if water pressur is on
  {

    if (GetWaterLevel() < targetLevel) //if target level is not reached
    {
      hc->SetDrain(1); // keep drainning
      return 0;        // return undone
    }
    if (GetWaterLevel() == targetLevel) // if target level is reached
    {
      hc->SetDrain(0);
      return 1;
    }
  }
  // if water pressur is low
  else if (hc->GetWaterPressur() == 0)
  {
    hc->SetDrain(0);
    return waterPressurError; // return error water pressur is low
  }
}

int Water::SetSink(int val)
{
  if (val == 0) // val is 0 the sink works automaticly
  {
    if (hc->GetWaterLevel() != 0) // if water is not empty sin k open
    {
      hc->SetSink(1);
      return 1;
    }
    else
    {
      hc->SetSink(0);
      return 0;
    }
  }
  if (val == 1) // if value is 1 keep the sink open even if water is empty used in centrifugate state
  {
    hc->SetSink(1);
  }
}

double Water::GetWaterLevel()
{
  return hc->GetWaterLevel();
}

int Water::GetWaterPressur()
{
  return hc->GetWaterPressur();
}
