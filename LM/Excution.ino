/*Done*/
#define WashPrepareSet 0 // set the water drain and heater
#define MotorSet 1       // set motor speed and motor rotation
#define SinkSet 2        // set sink at the end
#define ROTATIONTIME 5
#define CENTRFUGATETIME 2

#define waterPressurError -1

#include "Excution.h"

Excution::Excution()
{
  HC = new HWCC(); //initilize all hardware controle instances to HC
  water = new Water(HC);
  heater = new Heater(HC);
  control = new Control(HC);
  cycles = counter = 0; // starting values 0
}

bool Excution::Idle(int prog, int soap1, int soap2, int coins) // description in Excution.h
{
  if (control->WashStart()) // if start button is pressed
  {
    progI = new ProgramInstructions(prog); //create a new instant of programInstruction == passed prog
    if (coins < progI->GetCost())          //compare current prog cost and coins amount
      return false;                        //if not enugh dont start
    if (soap1 != 2)                        //check if soap 1 pices are enugh to start
      return false;
    if (soap2 != 3) //check if soap 2 pices are enugh to start
      return false;
    if (control->GetDoorLock() != 1) // check if the door is closed
      return false;
    //if this line is reached then all previous conditions are true and starting is possible
    control->SetLock(1); //lock the door
    return true;         //go tell the LM that its ok to start
  }
  return false; // start button isnt pressed
}

int Excution::Wash(int &timer, int stage, int &cnt) //description in Excution.h
{
  switch (cycles)
  {

  case WashPrepareSet:
    temp = washPrp(progI->GetWater(stage), progI->GetTemp(stage));
    if (temp == waterPressurError) // check if water pressur is low and return and error
      return waterPressurError;
    if (temp == 1) // when the desired water level is reached
    {
      timer = -1;        //reset the timer
      cycles = MotorSet; //go to next wash cycle
    }
    break;

  case MotorSet: //this cycle is the motor sets (rotation , speed) and repeatitions
    if (stage != 4)
    {
      RotationTimeOne = ROTATIONTIME;        // set rotation time for the motor
      RotationTimeTOW = RotationTimeOne * 2; // set rotation time for the motor
    }
    else if (stage == 4) // if we are at the final wash stage open the sink and set new rotation time
    {
      water->SetSink(1);
      RotationTimeOne = CENTRFUGATETIME;     // set rotation time for the motor last stage
      RotationTimeTOW = RotationTimeOne * 2; // set rotation time for the motor last stage
    }

    if (motorPrp(timer, cnt, progI->GetSpeed(stage), progI->GetReps(stage), progI->GetTemp(stage)))
    // when motor cycle done ( motor rotated for desired time and repeated acording to the program stage defined in program execution)
    {
      water->SetSink(0); // closes the sink if opened at final wash stage
      if (stage == 4)
        control->SetLock(0); // if this was final stage unlock
      cycles = SinkSet;      // go to next cycle
    }
    break;
  case SinkSet:
    if (sink()) //when water is empty
    {
      cycles = WashPrepareSet; // reset cycle
      return 1;                // return to lm that wash is doen
    }
    break;
  }
  return 0;
}

int Excution::washPrp(double wL, int Tmp) // water preperation stage
{
  heater->SetHeater(Tmp, water->GetWaterLevel()); // set the desired temprature and check water level
  temp1 = water->SetDrain(wL);
  if (temp1 == waterPressurError) // check water pressur and return an error if its low
    return waterPressurError;
  if (temp1 == 1) //when desired water level reached return true
    return 1;
  return 0;
}

bool Excution::motorPrp(int &t, int &rep, int speed, int repeats, int tmp) // motor preparation level
{
  heater->SetHeater(tmp, water->GetWaterLevel()); // the heater is set again
  if (rep < repeats)                              //check how many time the motor should repeat
  {
    
    if (t == 0)
    {
      control->SetRotation(true);
      control->SetSpeed(speed);
    }
    if (t == RotationTimeOne)      //when time is reached // should be 1 min
      control->SetRotation(false); //reverce rotation

    if (t == RotationTimeTOW) //when time is reached reset and increase repeat counter
    {
      t = 0;
      rep++;
    }
    return false; //as long as the repeats are not enugh return false
  }
  rep = 0;
  heater->SetHeater(0, 0); //turn heater off
  water->SetDrain(0);      //turn drain off
  control->SetSpeed(0);    //turn motor off
  return true;             //when repeats are enugh return true so wash goes to next  stage
}

bool Excution::sink()
{
  if (water->SetSink(0) == 0) //when water level is 0 return true
  {
    return true;
  }
  return false;
}

bool Excution::safeMode() //actions in safe mode
{

  heater->SetHeater(0, water->GetWaterLevel()); //turn heat off
  water->SetDrain(0);                           //turn drain off
  if (water->SetSink(0) == 0)                   //open sink and check if water is empty
  {
    control->SetLock(0); //unlok
    return true;         // if tank is empty
  }
  return false; //if tank is not empty
}

int Excution::waterPressur() // returns water prfessur to check in safe mode
{
  return water->GetWaterPressur();
}
