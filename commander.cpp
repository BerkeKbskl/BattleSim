#include "commander.h"

Commander::Commander() : Cavalry() {
    speed = 1.0;
    health=100;
    attackPower=1;
    defensePower = 5;
    img.load(":images/images/commander.jpeg");
}
