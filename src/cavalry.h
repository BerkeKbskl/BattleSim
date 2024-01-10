#ifndef CAVALRY_H
#define CAVALRY_H

#include "unit.h"

/**
 * @brief The Cavalry class represents a cavalry unit in a game scenario.
 *
 * This class is inherits the Unit class, introducing properties and functionality
 * specific to cavalry units.
 */
class Cavalry : public Unit
{

public:

    /**
     * @brief Constructor for the Cavalry class.
     */
    Cavalry();

protected:

    double chargePower; ///< The power associated with the cavalry charge.
    bool isChargeMode; ///< Flag indicating whether the cavalry is in charge mode.

    /**
     * @brief Overrides the base class attack function to provide specific behavior for cavalry units.
     * @param enemy The enemy unit to attack.
     * @return The damage inflicted on the enemy unit.
     */
    int attack(Unit& enemy) override;

};

#endif // CAVALRY_H

