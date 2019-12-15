#ifndef HCHEATER_H
#define HCHEATER_H

class HCHeater
{
public:
    virtual void SetHeater(int value) = 0;
    virtual int GetTemp() = 0;
};

#endif
