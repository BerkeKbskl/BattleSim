#ifndef PLAYER_H
#define PLAYER_H

#define A_Count 4
#define C_Count 4
#define I_Count 8

#include "unit.h"
#include "scenario.h"

class Player
{
public:
    Player();
    virtual void deployUnits(Scenario) = 0;
    vector<Unit*> units;

protected:
    const int artilleryCount = A_Count, cavalryCount = C_Count, infantryCount = I_Count;
    QColor color;
};

#endif // PLAYER_H
