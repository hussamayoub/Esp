#ifndef HCWater_H
#define HCWater_H

class HCWater
{
public:
    virtual double GetWaterLevel() = 0;
    virtual int GetWaterPressur() = 0;
    virtual void SetSink(int value) = 0;
    virtual void SetDrain(int value) = 0;
};
#endif
