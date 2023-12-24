#ifndef PLAYER_H
#define PLAYER_H



#include "unit.h"
#include "scenario.h"

class Player
{
public:
    Player();
    virtual void deployUnits(Scenario) = 0;
    vector<Unit*> units;

protected:
    void createUnits(list<QString>);
    Scenario scenario = 0;
    QColor color;
};

#endif // PLAYER_H
