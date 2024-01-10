#ifndef ARTILLERY_H
#define ARTILLERY_H

#include "unit.h"

/**
 * @brief The Artillery class represents an artillery unit in a game scenario.
 *
 * This class inherits the Unit class and introduces specific functionality
 * for artillery units, including shooting, attacking, drawing, and obtaining the attack collider.
 */
class Artillery : public Unit
{
public:

    /**
     * @brief Constructor for the Artillery class.
     */
    Artillery();

    /**
     * @brief Function to perform a shot with the artillery unit.
     * @return True if the shot is successful; otherwise, false.
     */
    bool shoot();

    /**
     * @brief Overrides the base class attack function to provide specific behavior for artillery units.
     * @param enemy The enemy unit to attack.
     * @return The damage inflicted on the enemy unit.
     */
    int attack(Unit& enemy) override;

    /**
     * @brief Overrides the base class draw function to provide custom drawing for artillery units.
     * @param painter The QPainter to use for drawing.
     */
    void draw(QPainter* painter) override;

    /**
     * @brief Overrides the base class function to provide the attack collider for artillery units.
     * @return A QPainterPath representing the attack collider.
     */
    QPainterPath getAttackCollider() const override;

private:
    int meleePower; ///< The melee power of the artillery unit.
    int ammo; ///< The ammunition available for the artillery unit.

};

#endif // ARTILLERY_H

