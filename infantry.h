#ifndef INFANTRY_H
#define INFANTRY_H

#include "unit.h"

class Infantry : public Unit
{
public:
    Infantry();
    void melee();

private:
    double firePower;
};

#endif // INFANTRY_H
