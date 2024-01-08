#include "infantry.h"
/**
 * @brief Constructs an Infantry object.
 *
 * This constructor initializes the Infantry object with default values for speed, health,
 * attack power, defense power, ammo, and image. It also loads the artillery image.
 */
Infantry::Infantry() : Unit() {
    speed = 1;
    health=100;
    attackPower=2;
    defensePower = 3;
    img.load(":images/images/infantry.png");
}

