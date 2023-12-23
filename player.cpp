#include "player.h"
#include "artillery.h"
#include "cavalry.h"
#include "infantry.h"

Player::Player()
{

    for(int i=0;i<infantryCount;i++){
        units.push_back(new Infantry());
    }

    for(int i=0;i<artilleryCount;i++){
        units.push_back(new Artillery());
    }

    for(int i=0;i<cavalryCount;i++){
        units.push_back(new Cavalry());
    }

}
