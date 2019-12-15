#include "HWCC.h"
#include "unistd.h"

#define OUT_GROUP2 0
#define OUT_GROUP1 1
#define OUT_STROBE 2
#define OUT_KEYSELECT 3
#define OUT_BUZZER 4
#define OUT_HEATER 5
#define OUT_SPEED2 6
#define OUT_SPEED1 7
#define OUT_DATAC 8
#define OUT_DATAB 9
#define OUT_DATAA 10
#define OUT_MOTOR_RL 11
#define OUT_SOAP1 12
#define OUT_SINK 13
#define OUT_DRAIN 14
#define OUT_LOCK 15
#define IN_W2 16
#define IN_W1 17
#define IN_T2 18
#define IN_T1 19
#define IN_IN3 20
#define IN_IN2 21
#define IN_IN1 22
#define IN_IN0 23

HWCC::HWCC()
{
  Wire.begin();           // start I2C
  centipede.initialize(); // set all registers to default
  init();
}
void HWCC::Strobe()
{

  centipede.digitalWrite(OUT_STROBE, LOW);
  delay(80);
  centipede.digitalWrite(OUT_STROBE, HIGH);
  delay(10);
}

//coins leds
void HWCC::SetLedTen(int led)
{
  int group1 = 0, group2 = 0, datac = 0, datab = 0, dataa = 0;
  if (led == 1)
  {
    dataa = 1;
  }
  if (led == 2)
  {
    dataa = 1;
    datab = 1;
  }
  if (led == 3)
  {
    dataa = 1;
    datab = 1;
    datac = 1;
  }
  Strobe();
  centipede.digitalWrite(OUT_GROUP1, group1);
  centipede.digitalWrite(OUT_GROUP2, group2);
  centipede.digitalWrite(OUT_DATAC, datac);
  centipede.digitalWrite(OUT_DATAB, datab);
  centipede.digitalWrite(OUT_DATAA, dataa);
}
void HWCC::SetLedFifty(int led)
{
  int group1 = 1, group2 = 0, datac = 0, datab = 0, dataa = 0;
  if (led == 1)
  {
    dataa = 1;
  }
  if (led == 2)
  {
    dataa = 1;
    datab = 1;
  }
  if (led == 3)
  {
    dataa = 1;
    datab = 1;
    datac = 1;
  }
  Strobe();
  centipede.digitalWrite(OUT_GROUP1, group1);
  centipede.digitalWrite(OUT_GROUP2, group2);
  centipede.digitalWrite(OUT_DATAC, datac);
  centipede.digitalWrite(OUT_DATAB, datab);
  centipede.digitalWrite(OUT_DATAA, dataa);
}
void HWCC::SetLedTowhundreds(int led)
{
  int group1 = 0, group2 = 1, datab = 0, dataa = 0, datac = 0;
  if (led == 1)
  {
    dataa = 1;
  }
  if (led == 2)
  {
    dataa = 1;
    datab = 1;
  }
  Strobe();
  centipede.digitalWrite(OUT_GROUP1, group1);
  centipede.digitalWrite(OUT_GROUP2, group2);
  centipede.digitalWrite(OUT_DATAB, datab);
  centipede.digitalWrite(OUT_DATAA, dataa);
  centipede.digitalWrite(OUT_DATAC, datac);
}
void HWCC::Clear()
{
  Strobe();
  centipede.digitalWrite(OUT_GROUP1, LOW);
  centipede.digitalWrite(OUT_GROUP2, LOW);
  centipede.digitalWrite(OUT_DATAC, LOW);
  centipede.digitalWrite(OUT_DATAB, LOW);
  centipede.digitalWrite(OUT_DATAA, LOW);
  Strobe();
  centipede.digitalWrite(OUT_GROUP1, HIGH);
  centipede.digitalWrite(OUT_GROUP2, LOW);
  centipede.digitalWrite(OUT_DATAC, LOW);
  centipede.digitalWrite(OUT_DATAB, LOW);
  centipede.digitalWrite(OUT_DATAA, LOW);
  Strobe();
  centipede.digitalWrite(OUT_GROUP1, LOW);
  centipede.digitalWrite(OUT_GROUP2, HIGH);
  centipede.digitalWrite(OUT_DATAB, LOW);
  centipede.digitalWrite(OUT_DATAA, LOW);
  centipede.digitalWrite(OUT_DATAA, LOW);
}

// soap
void HWCC::SetLedSoapOne(int val)
{
  centipede.digitalWrite(OUT_SOAP1, val);
}
void HWCC::SetLedSoapTow(int coins, int soapled)
{
  int datab = 0, dataa = 0;
  if (coins == 1)
    dataa = 1;
  if (coins == 2)
  {
    dataa = 1;
    datab = 1;
  }
  Strobe();
  centipede.digitalWrite(OUT_GROUP1, LOW);
  centipede.digitalWrite(OUT_GROUP2, HIGH);
  centipede.digitalWrite(OUT_DATAA, dataa);
  centipede.digitalWrite(OUT_DATAB, datab);
  centipede.digitalWrite(OUT_DATAC, soapled);
}

//Heater
void HWCC::SetHeater(int value)
{
  if (value == 0)
  {
    centipede.digitalWrite(OUT_HEATER, HIGH);
  }
  if (value == 1)
  {
    centipede.digitalWrite(OUT_HEATER, LOW);
  }
}
int HWCC::GetTemp()
{

  int temp1, temp2;
  temp1 = centipede.digitalRead(IN_T1);
  temp2 = centipede.digitalRead(IN_T2);
  if (temp1 & temp2)
    return 3;
  else if (!temp1 & temp2)
    return 2;
  else if (temp1 & !temp2)
    return 1;
  else if (!temp1 & !temp2)
    return 0;
  else
    return 999;
}

//water
double HWCC::GetWaterLevel()
{
  int wat1 = centipede.digitalRead(IN_W1);
  int wat2 = centipede.digitalRead(IN_W2);
  if (wat1 && wat2)
    return 100;
  if (!wat1 && !wat2)
    return 0;
  if (!wat1 && wat2)
    return 66.6;
  if (wat1 && !wat2)
    return 33.3;
  //return 101;
}

int HWCC::GetWaterPressur()
{
  centipede.digitalWrite(OUT_KEYSELECT, LOW);
  if (centipede.digitalRead(IN_IN0))
    return 1;
  else
    return 0;
}
void HWCC::SetSink(int value)
{
  if (value == 1)
    centipede.digitalWrite(OUT_SINK, HIGH);
  else if (value == 0)
    centipede.digitalWrite(OUT_SINK, LOW);
}
void HWCC::SetDrain(int value)
{
  if (value == 1)
    centipede.digitalWrite(OUT_DRAIN, HIGH);
  else if (value == 0)
    centipede.digitalWrite(OUT_DRAIN, LOW);
}

//prog leds
void HWCC::LedsOff()
{
  Strobe();
  centipede.digitalWrite(OUT_GROUP1, HIGH);
  centipede.digitalWrite(OUT_GROUP2, HIGH);
  centipede.digitalWrite(OUT_DATAC, LOW);
  centipede.digitalWrite(OUT_DATAB, LOW);
  centipede.digitalWrite(OUT_DATAA, LOW);
}

void HWCC::SetLedProg(int val)
{
  int dataa = 0, datab = 0, datac = 0;
  if (val == 0)
    dataa = 1;
  else if (val == 1)
    datab = 1;
  else if (val == 2)
    datac = 1;
  Strobe();
  centipede.digitalWrite(OUT_GROUP1, HIGH);
  centipede.digitalWrite(OUT_GROUP2, HIGH);
  centipede.digitalWrite(OUT_DATAC, datac);
  centipede.digitalWrite(OUT_DATAB, datab);
  centipede.digitalWrite(OUT_DATAA, dataa);
}

//controle
int HWCC::SetLock(int val)
{
  if (val == 0)
    centipede.digitalWrite(OUT_LOCK, LOW);
  else if (val == 1)
    centipede.digitalWrite(OUT_LOCK, HIGH);
}
void HWCC::SetSpeed(int val)
{
  if (val == 0)
  {
    centipede.digitalWrite(OUT_SPEED1, HIGH);
    centipede.digitalWrite(OUT_SPEED2, HIGH);
  }
  else if (val == 1)
  {
    centipede.digitalWrite(OUT_SPEED1, LOW);
    centipede.digitalWrite(OUT_SPEED2, HIGH);
  }
  else if (val == 2)
  {
    centipede.digitalWrite(OUT_SPEED1, HIGH);
    centipede.digitalWrite(OUT_SPEED2, LOW);
  }
  else if (val == 3)
  {
    centipede.digitalWrite(OUT_SPEED1, LOW);
    centipede.digitalWrite(OUT_SPEED2, LOW);
  }
}
void HWCC::SetRotation(int val)
{
  if (val == 0)
    centipede.digitalWrite(OUT_MOTOR_RL, HIGH);
  else if (val == 1)
    centipede.digitalWrite(OUT_MOTOR_RL, LOW);
}

//inputs
int HWCC::GetButton()
{
  int in3, in2, in1, in0;
  // returns coin10=0 coin50=1 coin200=2  Clear=3 program=4 start=5
  //debounce
  //press and hold
  //check last button while high
  centipede.digitalWrite(OUT_KEYSELECT, HIGH);
  in0 = centipede.digitalRead(IN_IN0);
  in1 = centipede.digitalRead(IN_IN1);
  in2 = centipede.digitalRead(IN_IN2);
  in3 = centipede.digitalRead(IN_IN3);

  if (in3 & !in2 & !in1 & !in0)
    return 0;
  else if (!in3 & in2 & !in1 & !in0)
    return 1;
  else if (!in3 & !in2 & in1 & !in0)
    return 2;
  else if (in0 & !in3)
    return 5;
  else if (in3 & in2 & in1)
    return 3;
  else if (in3 & in0)
    return 4;

  else
    return 999;
}
int HWCC::GetSwitchDoorLock()
{
  centipede.digitalWrite(OUT_KEYSELECT, LOW);
  if (centipede.digitalRead(IN_IN3))
    return 1;
  else
    return 0;
}
int HWCC::GetSwitchSoap2()
{
  centipede.digitalWrite(OUT_KEYSELECT, LOW);
  if (centipede.digitalRead(IN_IN2))
    return 1;
  else
    return 0;
}

int HWCC::GetSwitchSoap1()
{
  centipede.digitalWrite(OUT_KEYSELECT, LOW);
  if (centipede.digitalRead(IN_IN1))
    return 1;
  else
    return 0;
}

void HWCC::init()
{
  for (int i = 0; i <= 15; i++)
  {
    centipede.pinMode(i, OUTPUT);
  }
  centipede.digitalWrite(OUT_GROUP2, LOW);
  centipede.digitalWrite(OUT_GROUP1, LOW);
  centipede.digitalWrite(OUT_STROBE, LOW);
  centipede.digitalWrite(OUT_KEYSELECT, HIGH);
  centipede.digitalWrite(OUT_BUZZER, HIGH);
  centipede.digitalWrite(OUT_HEATER, HIGH);
  centipede.digitalWrite(OUT_SPEED2, HIGH);
  centipede.digitalWrite(OUT_SPEED1, HIGH);
  centipede.digitalWrite(OUT_DATAC, LOW);
  centipede.digitalWrite(OUT_DATAB, LOW);
  centipede.digitalWrite(OUT_DATAA, LOW);
  centipede.digitalWrite(OUT_MOTOR_RL, LOW);
  centipede.digitalWrite(OUT_SOAP1, LOW);
  centipede.digitalWrite(OUT_SINK, LOW);
  centipede.digitalWrite(OUT_DRAIN, LOW);
  centipede.digitalWrite(OUT_LOCK, LOW);
}
