#ifndef ARTILLERY_H
#define ARTILLERY_H

#include "unit.h"

class Artillery : public Unit
{
public:
    Artillery();
    void shoot();
    void attack(Unit&);


private:
    int ammo;
};

#endif // ARTILLERY_H
