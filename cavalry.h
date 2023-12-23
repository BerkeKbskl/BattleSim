#ifndef CAVALRY_H
#define CAVALRY_H

#include "unit.h"

class Cavalry : public Unit
{

public:
    Cavalry() ;

    void charge();
    void attack(Unit&);

private:


};

#endif // CAVALRY_H
