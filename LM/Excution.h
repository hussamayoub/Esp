/*done*/
#ifndef EXCUTION_H
#define EXCUTION_H

#include "Water.h"
#include "Heater.h"
#include "Control.h"
#include "ProgramInstructions.h"
#include "HWCC.h"

class Excution
{
private:
int  RotationTimeOne ,RotationTimeTOW; // time of rotation 
int counter;  //counter is used to compare each stage repeatitions
  HWCC *HC; 
  Water *water;
  Heater *heater;
  Control *control;
  ProgramInstructions *progI;
  int cycles; // cycles is used in wash function to determine at which stage the wash is
  //first (sub state) here I set the heater and water drain functions returns true when desired water level is reached
  int temp , temp1;
  int washPrp(double wL , int Tmp ); 
  //second sub state here I return true when the moror did rotate as many times as requiered by the program
  bool motorPrp(int &t, int &rep, int speed, int repeats , int tmp);
  //sink returns true when water level is 0
  bool sink();
  

public:
  Excution();//constructor
  bool Idle(int prog, int soap1, int soap2, int coins );/*this state is continuesly checking for coins 
                                                        soap switches program select button door lock 
                                                        basicly all the needed conditions to start the wash 
                                                        it returns true when it is possible to start a program*/
  
  /*this function is used for the 4 wash stages prewash / mainwash1 / mainwash 2 / finalwash
  the parameters are used to pass which stage is the function used for :
  if stage is prewash the three sub state functions are called passing the parameters from program instuctions class .
  so the function washprp motorprp and sink will act according to the description in program instructions
  cntr is a variable in LM to keep track of repeats already done
  */
  int Wash(int &timer ,  int stage , int &cntr);      
  bool safeMode(); // safe mode action
  int waterPressur(); // returns water pressur to be used in sae mode  check

  
};
#endif
