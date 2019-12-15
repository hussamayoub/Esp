/*Done*/
#ifndef PROGRAMINSTRUCTIONS_H
#define PROGRAMINSTRUCTIONS_H

struct program
{
  double water1, water2, water3;                       // water value needed by each stage
  int heat1, heat2, reps1, reps2, heat3, reps3, reps4; // temp and repeats needed by each stage
};

class ProgramInstructions
{
private:
  int cost; // program cost
  program prog;

public:
  ProgramInstructions(int prog); // constructor
  double GetWater(int stage);    // returns needed watere at passed stage
  int GetTemp(int stage);        // returns desired temp at passed stage
  int GetSpeed(int stage);       // returns desired smotor speed at passed stage
  int GetCost();                 // returns program cost
  int GetReps(int stage);        // return repeatitions of passed stage
};
#endif
