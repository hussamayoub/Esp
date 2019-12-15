/*Done*/

#define TEN_CENTS_BUTTON 0
#define FIFTY_CENTS_BUTTON 1
#define TH_CENTS_BUTTON 2
#define CLEAR_CENTS_BUTTON 3

#include "Coins.h"

Coins::Coins(HCCoins *HC) //constructor set initial values to 0 and assign the hw control class
{
  hc = HC;
  ten = fifty = towhundreds = setleds = tim = hold = 0;
}

int Coins::GetAmount()
{
  return ten + fifty + towhundreds; // return total money amount
}

void Coins::SetLeds()
{
  hc->SetLedTen(ten / 10);                  // set number of ten cents leds
  hc->SetLedFifty(fifty / 50);              // set number of 50 cents leds
  hc->SetLedTowhundreds(towhundreds / 200); // set number of 200 cents leds
  setleds = 0;                              //deactivate the function using a private variable
}

void Coins::init()
{
  hold = hc->GetButton();   // check for button press
  if (hold != 999)          // if a button  pressed
    lastbutton = hold;      // store the value in last button
  if (millis() - tim > 200) // debounce time
    hold = hc->GetButton(); // after the time check the button again
  if (hold == 999)          // is btton is up
  {
    button = lastbutton; // store the temp button value in button variable
    lastbutton = 999;    // reset temp button value
    tim = millis();      // reset timer
  }

  switch (button) // switch statment of button value
  {
  case TEN_CENTS_BUTTON: // button ten cents pressed
    if (ten < 30)        // check ten cents amount
      ten += 10;         //add if possible
    setleds = true;      // activate set leds function
    break;
  case FIFTY_CENTS_BUTTON: //button fifty cents pressed
    if (fifty < 150)       //check fifty cents amount
      fifty += 50;         //add if possible
    setleds = true;        // activate set leds function
    break;
  case TH_CENTS_BUTTON:    //button tow hundreds
    if (towhundreds < 400) // check amount
      towhundreds += 200;  //add if possible
    setleds = true;        // activate set leds function
    break;
  case CLEAR_CENTS_BUTTON: //buton clear is pressed
    ten = fifty = towhundreds = 0;
    hc->Clear();
    setleds = true; // activate set leds function
    break;

  default: //if the read is still 999 no button pressed

    break;
  }
  if (setleds)
    Coins::SetLeds(); // set leds if change happend

  button = 999; // reset button value
}

int Coins::getTHundredsLeds()
{
  return towhundreds / 200;
}

void Coins::clear()
{
  ten = fifty = towhundreds = 0;
  hc->Clear();
}