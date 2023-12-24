#include "cavalry.h"

Cavalry::Cavalry() : Unit() {
    speed = 10;
    health=800;
    attackPower=60;
    defensePower = 40;
    img.load(":images/images/cavalry.png");
}

