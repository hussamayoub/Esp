/*done*/
#ifndef CONTROL_H
#define CONTROL_H

#include "HCControl.h"

class Control
{
private:
  int lock;      //keep lock value
  HCControl *hc; // Hard ware control interface

public:
  Control(HCControl *HC);     // constructor
  void SetLock(bool val);     // sets the door lock true or false
  void SetSpeed(int val);     //sets rotation speed
  void SetRotation(bool val); // set rotation direction
  bool GetDoorLock();         //get the door close switch status
  bool GetLock();             //get lock status
  bool WashStart();           //get start button press
};
#endif
