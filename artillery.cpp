#include "artillery.h"
#include <iostream>

Artillery::Artillery() : Unit() {
    speed = 5;
    defensePower = 20;
    img.load(":images/images/artillery.png");
}

