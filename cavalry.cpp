#include "cavalry.h"

Cavalry::Cavalry() : Unit() {
    speed = 10;
    health=100;
    attackPower=1;
    defensePower = 5;
    img.load(":images/images/cavalry.png");
}

