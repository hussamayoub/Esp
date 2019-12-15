#ifndef HCCOINS_H
#define HCCOINS_H

class HCCoins
{

public:
  virtual void SetLedTen(int led) = 0;
  virtual void SetLedFifty(int led) = 0;
  virtual void SetLedTowhundreds(int led) = 0;
  virtual void Clear() = 0;
  virtual int GetButton() = 0;
};

#endif
