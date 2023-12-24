#include "artillery.h"
#include <iostream>

Artillery::Artillery() : Unit() {
    speed = 2;
    health=300;
    attackPower=35;
    defensePower = 15;
    img.load(":images/images/artillery.png");
}

