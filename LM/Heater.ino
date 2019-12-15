/*Done*/
#include "Heater.h"

Heater::Heater(HCHeater *HC)
{
  this->hc = HC;
}

int Heater::GetTemp()
{
  return hc->GetTemp();
}

void Heater::SetHeater(int targetTemp, double waterLevel)
{
  if (waterLevel >= 33.3) //check the critical condition
  {
    if ((this->GetTemp()) < targetTemp) //if current temp less than desired temp
    {
      hc->SetHeater(1); //turn heater on
    }
    else if ((this->GetTemp()) >= targetTemp) //if desired temp reached
    {
      hc->SetHeater(0); // turn heater off
    }
  }
  else                //if water isnt atleast third in the tank
    hc->SetHeater(0); // dont start the heater
}
