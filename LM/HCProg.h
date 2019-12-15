#ifndef HWCPROG_H
#define HWCPROG_H

class HCProg
{

public:
    virtual void SetLedProg(int val) = 0;
    virtual int GetButton() = 0;
    virtual void LedsOff() = 0;
};
#endif
