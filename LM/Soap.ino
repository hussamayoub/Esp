/*done*/
#include "Soap.h"

Soap::Soap(HCSoap *HC)
{
  //set initial values and assigne HWCC instance
  soap1 = soap2 = soap1temp = soap2temp = reset1 = reset2 = reset = 0;
  this->hc = HC;
}

int Soap::GetSoapOne() { return soap1; }

int Soap::GetSoapTow() { return soap2; }

void Soap::init(int val)
{
  if (val) // if the value is 1
  {
    if (hc->GetSwitchSoap1() == 1)                     // check if soap1 switch is high
      soap1temp = 1;                                   //set the temp value to 1
    if ((hc->GetSwitchSoap1() == 0) && soap1temp == 1) // if the switch was high before going low
    {
      if (soap1 < 2) // if soap1 is not full yet
      {
        soap1++;    // add soap 1
        time1 = -1; // reset blinking timer
      }
      soap1temp = 0; // reset temp value
    }

    if (hc->GetSwitchSoap2() == 1)                     // check if soap2 switch is high
      soap2temp = 1;                                   //set temp value to 1
    if ((hc->GetSwitchSoap2() == 0) && soap2temp == 1) //if the switdch was high before going low
    {
      if (soap2 < 3) //if soap2 is not full yet
      {
        soap2++;    // add soap2
        time2 = -1; //reset timer
      }
      soap2temp = 0; //empty temp value
    }
  }
}

void Soap::setLeds(int coinsth)
{
  switch (soap1) // check number of soap1 pices
  {
  case 0:                 // if empty
    hc->SetLedSoapOne(0); //turn the led off
    break;
  case 2:
    hc->SetLedSoapOne(1); //if full turn the led on
    break;

  default: // else blink the led every second
    if (time1 == 1)
    {
      hc->SetLedSoapOne(1);
    }
    if (time1 >= 2)
    {
      hc->SetLedSoapOne(0);
      reset1 = 1;
    }
    break;
  }

  switch (soap2) //// check number of soap2 pices
  {
  case 0: //if empty turn the led off
    hc->SetLedSoapTow(coinsth, 0);
    break;
  case 3: //if full turn the led on
    hc->SetLedSoapTow(coinsth, 1);
    break;

  default: //else blink the led every second
    if (time2 == 1)
      hc->SetLedSoapTow(coinsth, 1);
    if (time2 >= 2)
    {
      hc->SetLedSoapTow(coinsth, 0);
      reset2 = 1;
    }
    break;
  }
  if (reset1) //if led went on then off
  {
    time1 = 0;  // reset timer
    reset1 = 0; //reset flag low
  }
  if (reset2) //if led went on then off
  {
    time2 = 0;  //reset timer
    reset2 = 0; //reset flag low
  }
}

void Soap::clearSoap1() { soap1 = 0; }
void Soap::clearSoap2() { soap2 = 0; }
