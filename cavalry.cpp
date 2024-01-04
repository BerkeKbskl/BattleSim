#include "cavalry.h"

Cavalry::Cavalry() : Unit() {
    speed = 1.6;
    health=100;
    attackPower=1;
    defensePower = 5;
    img.load(":images/images/cavalry.png");
}

