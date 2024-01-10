#include "cavalry.h"

Cavalry::Cavalry() : Unit() {
    speed = 1.6;
    health=100;
    attackPower=1;
    chargePower=5;
    defensePower = 5;
    isChargeMode=true;
    img.load(":images/images/cavalry.png");
}

int Cavalry::attack(Unit& enemy){
    if(isChargeMode){
        chargePower=enemy.getHealth()*20/100;
        attackPower*=chargePower;
        isChargeMode=false;
    }
    else if(enemy.getHealth()-attackPower<=0){
        isChargeMode=true;
    }
    else if(attackPower==chargePower){
        attackPower/=chargePower;
    }
    return Unit::attack(enemy);
}
