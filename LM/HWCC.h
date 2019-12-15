#ifndef HWCC_H
#define HWCC_H

#include <Wire.h>
#include <Centipede.h>
#include <Arduino.h>
#include "HCCoins.h"
#include "HCSoap.h"
#include "HCHeater.h"
#include "HCWater.h"
#include "HCProg.h"
#include "HCControl.h"

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

class HWCC : public HCCoins, public HCSoap, public HCHeater, public HCWater, public HCProg, public HCControl
{
  Centipede centipede;
  int soapOnePieces;
  int soapTowPieces;
  

public:
  HWCC();

  /*Coins Interface*/
  void Strobe();
  void SetLedTen(int led);
  void SetLedFifty(int led);
  void SetLedTowhundreds(int led);
  void Clear();

  /*Soap interface*/
  void SetLedSoapOne(int val);
  void SetLedSoapTow(int coins, int soapled);

  /*Heater interface */
  void SetHeater(int value);
  int GetTemp();

  /*water interface*/
  double GetWaterLevel();
  int GetWaterPressur();
  void SetSink(int value);
  void SetDrain(int value);

  /*prog interface*/
  void SetLedProg(int val);
  void LedsOff();

  /*control interface*/
  int SetLock(int val);
  void SetSpeed(int val);
  void SetRotation(int val);

  /*//////////////////////////////////intputs////////////////////////////////////*/
  int GetButton();
  int GetSwitchDoorLock();
  int GetSwitchSoap1();
  int GetSwitchSoap2();
  void init();
};

#endif
