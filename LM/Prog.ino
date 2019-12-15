#define PROGA 0 // define program A , B , C
#define PROGB 1
#define PROGC 2
#include "Prog.h"

Prog::Prog(HCProg *HC)
{
  prog = PROGA;             // set default program to A
  this->hc = HC;            // initilize hardware controle instance
  hold = tim = 0; // set initial values
  setleds = 1;
}

void Prog::init(bool val)
{
  if (val)
  {
    hold = hc->GetButton();   // check for button press
    if (hold == 4)            // if the select button program pressed
      lastbutton = hold;      // store the value in last button
    if (millis() - tim > 500) // debounce time
      hold = hc->GetButton(); // after the time check the button again
    if (hold == 999)          // is btton is up
    {
      button = lastbutton; // store the temp button value in button variable
      lastbutton = 999;    // reset temp button value
      tim = millis();      // reset timer
    }

    if (button == 4) // if select button value is equal to button variable
    {
      prog += 1;         // increase current program
      setleds = 1;       //activate set leds function
      if (prog == 3) //if the current program is C
      {
        prog = PROGA; // go back to program A
        setleds = 1;
      }
    }

    if (setleds) // if the function is activated set the leds (program changed)
    {
      hc->SetLedProg(prog); //set leds again
      setleds = false;      // deactivate setLeds function
    }
  }
  button = 999; // reset button value
}
int Prog::GetProg() // return selected program
{
  return prog;
}


void Prog::safeMode(int val, int &tim)
{
  if (val == 1) //blink program led
  {
    if(tim == 0) // 1 second per blink
    hc->SetLedProg(prog);//set led on 
    if(tim >= 1)//after one second
    {
    hc->LedsOff();//set led off
    tim = -1;//reset time
    }
  }
  if(val == 0)//leds off
  {
    hc->LedsOff(); 
  }

  if(val == 2) // safe mode leds blink
  {
    hc->SetLedProg(PROGA); // blink all leds
    hc->SetLedProg(PROGB);
    hc->SetLedProg(PROGC);
    prog = PROGA; // reset progrram to a
  }

  if(val == 3)
  {
    hc->SetLedProg(prog); // set led back on 
  }
  setleds = 1; // activate set leds
}


