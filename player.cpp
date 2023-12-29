#include "player.h"
#include "artillery.h"
#include "cavalry.h"
#include "infantry.h"

Player::Player()
{

}
void Player::createUnits(QList<QString> unitTypes){
    for(QString type:unitTypes){
        if(type=="infantry"){units.push_back(new Infantry());}
        else if(type=="cavalry"){units.push_back(new Cavalry());}
        else if(type=="artillery"){units.push_back(new Artillery());}
    }
}
