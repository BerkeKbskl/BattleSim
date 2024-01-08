#ifndef CAVALRY_H
#define CAVALRY_H

#include "unit.h"

class Cavalry : public Unit
{

public:
    Cavalry() ;

protected:
    double chargePower;
    bool isChargeMode;
    int attack(Unit&) override;
};

#endif // CAVALRY_H
