#include "player.h"
#include "artillery.h"
#include "cavalry.h"
#include "commander.h"
#include "infantry.h"

Player::Player():scenario(0,0)
{
}


QVector<Unit*> Player::getUnits() const
{
    return units;
}


void Player::addUnits(Unit* unit)
{
    units.push_back(unit);
}


void Player::removeUnits(Unit* unit)
{
    units.erase(std::remove(units.begin(), units.end(), unit), units.end());
}


void Player::createUnits(QList<QString> unitTypes){
    for(const QString &type:unitTypes){
        if(type=="infantry"){addUnits(new Infantry());}
        else if(type=="cavalry"){addUnits(new Cavalry());}
        else if(type=="artillery"){addUnits(new Artillery());}
        else if(type=="commander"){addUnits(new Commander());}
    }
}
