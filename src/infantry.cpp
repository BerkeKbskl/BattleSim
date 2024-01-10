#include "infantry.h"

Infantry::Infantry() : Unit() {
    speed = 1;
    health=100;
    attackPower=2;
    defensePower = 3;
    img.load(":images/images/infantry.png");
}

