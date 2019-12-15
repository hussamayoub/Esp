#ifndef HCSOAP_H
#define HCSOAP_H

class HCSoap
{
public:
    virtual void SetLedSoapOne(int val) = 0;
    virtual void SetLedSoapTow(int coins, int soapled) = 0;
    virtual int GetSwitchSoap1() = 0;
    virtual int GetSwitchSoap2() = 0;
};

#endif
