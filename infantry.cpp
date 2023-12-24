#include "infantry.h"

Infantry::Infantry() : Unit() {
    speed = 5;
    health=500;
    attackPower=15;
    defensePower = 30;
    img.load(":images/images/infantry.png");
}

