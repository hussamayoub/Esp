

#define IDLE 0 //define states names
#define PREWASH 1
#define MAINWASH_1 2
#define MAINWASH_2 3
#define CENTRIFUGATE 4
#define SAFEMODE 5
#define END 6             //end define states names
#define SAFEMODE_TIMER 10 // safe mode wait time
#define ENDSTOPTIME 10    // end state wait time

#include "HWCC.h"
#include "Coins.h"
#include "Prog.h"
#include "Soap.h"
#include "Excution.h"

HWCC *HC;
Coins *coins;
Prog *prog;
Soap *soap;
Excution *ex;

int iTemp, initilize;                // stores wash function value to check for return // initilize activates/deactivates init functions
int state, lastState;                // wash state and a temp variable to store last state
int timer, progtimer, safeModeTimer; // timers
int counter;                         // used by wash function to store repeats done

void setup() // set initial values
{
  noInterrupts(); // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1B |= (1 << CS12);  // 256 prescaler
  TIMSK1 |= (1 << TOIE1); // enable timer overflow interrupt
  interrupts();           // enable all interrupts

  ex = new Excution();
  HC = new HWCC();
  coins = new Coins(HC);
  prog = new Prog(HC);
  soap = new Soap(HC);

  initilize = 1;
  progtimer = state = counter = safeModeTimer = 0;
  Serial.begin(9600);

  HC->init();
}

ISR(TIMER1_OVF_vect) // increas timers every 1 sec
{
  safeModeTimer++;
  timer++;
  soap->time1++;
  soap->time2++;
  progtimer++;
}

void safeModeCheck(int WashFunction, int &state)
{
  if (WashFunction == -1) // if washfunction value is -1 (low pressur)
  {
    progtimer = -1;    //reset program timer timer
    safeModeTimer = 0; //start safe mode timer
    lastState = state; // store the wash state when error happend
    state = SAFEMODE;  // go to safemode state
  }
}

void loop()
{
  coins->init();                            //coins tray start monitoring coins buttons
  soap->init(initilize);                    //soap start monitoring soap switches
  prog->init(initilize);                    // program start monitoring prog buttons
  soap->setLeds(coins->getTHundredsLeds()); // set soap leds acording to value implemented here to set coins 200 leds

  switch (state)
  {
  case IDLE: // IDle state
    // check if all conditions to start a program are met
    if (ex->Idle(prog->GetProg(), soap->GetSoapOne(), soap->GetSoapTow(), coins->GetAmount()))
    {
      initilize = 0;   // stop monitoring soap switches and program buttons
      coins->clear();  // clear coins
      state = PREWASH; // go to next state
    }
    break;

  case PREWASH:                                // prewash state
    iTemp = ex->Wash(timer, PREWASH, counter); //start prewash
    safeModeCheck(iTemp, state);               // check for water pressur error
    if (iTemp == 1)                            // if wash function is done
    {
      soap->clearSoap1(); // clear soap 1
      timer = 0;          // reset timer
      state = MAINWASH_1; // go to next stage
    }
    break;

  case MAINWASH_1:                                // main wash 1 stage
    iTemp = ex->Wash(timer, MAINWASH_1, counter); // start mainwash 1
    safeModeCheck(iTemp, state);                  // check for water pressur error
    if (iTemp == 1)                               // if mainwash 1 is done
    {
      soap->clearSoap2(); // clear soap 2
      state = MAINWASH_2; //go to next state
    }
    break;

  case MAINWASH_2:                                // main wash2 state
    iTemp = ex->Wash(timer, MAINWASH_2, counter); //start mainwash 2
    safeModeCheck(iTemp, state);                  // check rfor water pressur error
    if (iTemp == 1)                               // if mainwash 2 is done
      state = CENTRIFUGATE;                       // go to next state
    break;

  case CENTRIFUGATE:                            //final state
    if (ex->Wash(timer, CENTRIFUGATE, counter)) //start centrifugate and when its done ..
    {
      timer = 0;                // reset timer
      lastState = CENTRIFUGATE; //store last state
      state = END;              //go to End state
    }
    break;

  case SAFEMODE:                                              //safe mode state
    prog->safeMode(1, progtimer);                             // start blinking program led to indicate error
    if (ex->waterPressur() && safeModeTimer < SAFEMODE_TIMER) // if water pressur is back before time out
    {
      prog->safeMode(3, progtimer); // stop blinkking leds
      state = lastState;            // go back to last state before entering safemode
    }
    if (safeModeTimer >= SAFEMODE_TIMER) // if time is out
    {
      if (ex->safeMode()) // execute safemode sequence in execute class
      {
        soap->clearSoap1();   // to be discussed
        soap->clearSoap2();   // to be discussed
        timer = 0;            //reset timer
        lastState = SAFEMODE; //save last state
        state = END;          // go back to idle state
      }
    }
    break;

  case END:                         // end
    if (lastState == SAFEMODE)      //if end state is reached from safe mode
      prog->safeMode(2, progtimer); //blink progam leds to indicate error
    else                            // if program ended normally
      prog->safeMode(0, progtimer); // turn program leds off
    if (timer == ENDSTOPTIME)       // when end time is reached
    {
      initilize = 1; // initilize activate
      state = IDLE;  // set state to idle
    }
    break;
  }
}
