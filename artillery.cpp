#include "artillery.h"
#include <iostream>

Artillery::Artillery() : Unit() {
    speed = 2;
    defensePower = 20;
    img.load(":images/images/artillery.png");
}

