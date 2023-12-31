#ifndef PLAYER_H
#define PLAYER_H

#include "unit.h"
#include "scenario.h"

class Player
{
public:
    Player();
    virtual void deployUnits(Scenario) = 0;
    void addUnits(Unit*);
    void removeUnits(Unit*);
    vector<Unit*> getUnits() const;


protected:
    void createUnits(QList<QString>);
    Scenario scenario = 0;
    QColor color;
    vector<Unit*> units;
};

#endif // PLAYER_H
