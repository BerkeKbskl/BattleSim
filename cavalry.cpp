#include "cavalry.h"
/**
 * @brief Constructs an Cavalry object.
 *
 * This constructor initializes the Cavalry object with default values for speed, health,
 * attack power, defense power, ammo, and image. It also loads the artillery image.
 */
Cavalry::Cavalry() : Unit() {
    speed = 1.6;
    health=100;
    attackPower=1;
    defensePower = 5;
    img.load(":images/images/cavalry.png");
}

