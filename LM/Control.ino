/*done*/
#include "Control.h"

Control::Control(HCControl *HC) // constructor
{
  lock = 0; // when created lock is false
  hc = HC;
}

void Control::SetLock(bool val)
{
  hc->SetLock(val); // hardware controle instance sets the lock to passed value
  lock = val;       // store current lock state
}

void Control::SetSpeed(int val)
{
  hc->SetSpeed(val); // set speed acordin to passed val
}

void Control::SetRotation(bool val)
{
  hc->SetRotation(val); // set rotation ClockWise or CClockWise
}

bool Control::GetDoorLock()
{
  return hc->GetSwitchDoorLock(); //status of door switch
}

bool Control::GetLock()
{
  return lock; // return lock status
}

bool Control::WashStart()
{
  int i = hc->GetButton(); // check if the button pressed is equal to start button defined 5
  if (i == 5)
  {
    return true;
  }
  return false;
}
