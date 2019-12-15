//Done
#ifndef SOAP_H
#define SOAP_H

#include "HCSoap.h"

class Soap
{
private:
    /*reset1 & reset2 are used in setled function to check if a blinking cycle is finished to resest the timer
soap1 & soap2 are storing value of soap pices
soap1temp & soap2temp store value when a switch is set to up and wait untill the switch is set down
*/
    int reset1, reset2, soap1, soap2, soap1temp, soap2temp , reset;
    HCSoap *hc;

public:
    int time1, time2;          // timers increased every second in timer interrupt in LM
    Soap(HCSoap *HC);          //constructor
    int GetSoapOne();          //returns soap1
    int GetSoapTow();          //returns soap2
    void init(int val);        //if value is one soap class activates the switches check
    void setLeds(int coinsth); //set leds acording to soap1 and soap2 values
    void clearSoap1();         //clear soap1
    void clearSoap2();         //clear soap2
};
#endif
