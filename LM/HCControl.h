#ifndef HCCONTROL_H
#define HCCONTROL_H

class HCControl
{
public:
    virtual int SetLock(int val) = 0;
    virtual void SetSpeed(int val) = 0;
    virtual void SetRotation(int val) = 0;
    virtual int GetSwitchDoorLock() = 0;
    virtual int GetButton() = 0;
};
#endif
