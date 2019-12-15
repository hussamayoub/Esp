
#ifndef PROG_H
#define PROG_H

#include "HCProg.h" /* hardware control interface of programm */

class Prog
{
private:
  int hold, button, lastbutton, tim; //  used to store hold button value and debounce + timer
  HCProg *hc;
  int prog; // stores the current selected program
  bool setleds;

public:
  Prog(HCProg *HC);   //constructor
  void init(bool val); // monitor program select button
  int GetProg();      //return selected program
  void safeMode(int val,int &tim);  // blink led in safe mode
  
};
#endif
