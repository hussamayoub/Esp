/*Done*/
#define PROGA 0 // define program A , B , C
#define PROGB 1
#define PROGC 2

#define SPEEDPW 1 // define speed prewash main and final
#define SPEEDMN 2
#define SPEEDFNL 3
#include "ProgramInstructions.h"

ProgramInstructions::ProgramInstructions(int p)
{
  prog.water1 = prog.water2 = prog.water3 = 66.6;        // set default water levels for each stage
  prog.heat1 =0; 
  prog.heat2 = 2;                           // set temp level for each stage
  prog.reps1 = prog.reps2 = prog.reps3 = prog.reps4 = 1; // set repeatitions for each stage
  if (p == PROGA)                                        // if selected program is A
  {
    cost = 360; // set  ccost
  }
  else if (p == PROGB) // if selected program is B change initilized values above
  {
    prog.heat1 = 2; // heat at prewash
    cost = 480;     // cost
    prog.reps2 = 2; // repeats at main wash
    prog.reps3 = 2; // repeats at main wash2
  }

  else if (p == PROGC) // if program c is selected
  {
    prog.heat1 = 2;              // set temp at prewash
    prog.water2 = 100;           // set waterlevel at mainwash1
    prog.heat2 = 3;              // set temp at mainwash 1
    prog.reps2 = prog.reps3 = 3; // set reps
    prog.reps4 = 2;              // reps at final stage
    cost = 510;                  // cost
  }
}

/*
// constructor
  double GetWater(int stage);    
  int GetTemp(int stage);        
  int GetSpeed(int stage);       // returns desired smotor speed at passed stage
  int GetCost();                 // returns program cost
  int GetReps(int stage);        // return repeatitions of passed stage
*/
double ProgramInstructions::GetWater(int stage) // returns needed watere level at passed stage
{
  switch (stage)
  {
  case 1:
    return prog.water1;
    break;
  case 2:
    return prog.water2;
    break;
  case 3:
    return prog.water3;
    break;
  case 4:
    return 0;
    break;
  }
}

int ProgramInstructions::GetTemp(int stage) // returns desired temp at passed stage
{
  switch (stage)
  {
  case 1:
    return prog.heat1;
    break;
  case 2:
    return prog.heat2;
    break;
  default:
    return 0;
    break;
  }
}
int ProgramInstructions::GetSpeed(int stage)
{
  if (stage < 5) // check if passed value is acceptable
  {
    if (stage == 3) // if main wash 2 is passed return medium speed
      stage = SPEEDMN;
    if (stage == 4) // if final stage value is passed return fast speed
      stage = SPEEDFNL;
    return stage; // return speed (if 1 or 2 stays the stame)
  }
}

int ProgramInstructions::GetCost() //return cost
{
  return cost;
}

int ProgramInstructions::GetReps(int stage)
{
  switch (stage) // returns repeatitions according to passed stage
  {
  case 1: // all programs shares the prewash reps
    return 1;
    break;
  case 2:
    return prog.reps2;
    break;
  case 3:
    return prog.reps3;
    break;
  case 4:
    return prog.reps4;
    break;
  }
}
