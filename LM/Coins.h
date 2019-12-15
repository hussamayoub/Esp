/*Done*/
#ifndef COINS_H
#define COINS_H

#include "HCCoins.h"

class Coins
{
private:
    int tim, ten, fifty, towhundreds; // Time +  money variables
    int lastbutton, button, hold;     // int variables used to hold pressed button value and manage debounce
    HCCoins *hc;                      // hardware controle interface
    void SetLeds();                   // private functions to set leds according to money amount
    bool setleds;                     //bool to activate or de activate setleds function

public:
    Coins(HCCoins *HC);     //constructor
    int GetAmount();        //return money amount
    int getTHundredsLeds(); //return active 200 leds to use in soap 2 set led due to hardware limit
    void clear();           //clear money tray
    void init();            //init function "do your thing" as discussed in class
};
#endif
