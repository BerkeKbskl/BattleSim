#ifndef PLAYER_H
#define PLAYER_H

#include "unit.h"
#include "scenario.h"

/**
 * @brief The Player class represents a player in a game scenario.
 *
 * This class provides functionality for deploying and managing units in the game.
 */
class Player
{
public:

    /**
     * @brief Constructor for the Player class.
     */
    Player();

    /**
     * @brief Virtual function to deploy units in the game scenario.
     * @param scenario The game scenario in which units are deployed.
     */
    virtual void deployUnits(Scenario) = 0;

    /**
     * @brief Adds a unit to the player's collection.
     * @param unit The unit to be added.
     */
    void addUnits(Unit* unit);

    /**
     * @brief Removes a unit from the player's collection.
     * @param unit The unit to be removed.
     */
    void removeUnits(Unit* unit);

    /**
     * @brief Gets the collection of units owned by the player.
     * @return A QVector of Unit pointers representing the player's units.
     */
    QVector<Unit*> getUnits() const;

protected:

    /**
     * @brief Creates units based on the provided unit types.
     * @param unitTypes A QList of QString representing the types of units to create.
     */
    void createUnits(QList<QString> unitTypes);

    Scenario scenario; ///< The game scenario associated with the player.
    QColor color; ///< The color associated with the player.
    QVector<Unit*> units; ///< The collection of units owned by the player.

};

#endif // PLAYER_H

