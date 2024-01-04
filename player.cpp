#include "player.h"
#include "artillery.h"
#include "cavalry.h"
#include "infantry.h"

Player::Player():scenario(0,0)
{
}

/**
 * @brief Gets the vector of units owned by the player.
 *
 * @return A vector of Unit pointers owned by the player.
 */
QVector<Unit*> Player::getUnits() const
{
    return units;
}

/**
 * @brief Adds a unit to the player's collection.
 *
 * @param unit A pointer to the unit to be added.
 */
void Player::addUnits(Unit* unit)
{
    units.push_back(unit);
}

/**
 * @brief Removes a unit from the player's collection.
 *
 * @param unit A pointer to the unit to be removed.
 */
void Player::removeUnits(Unit* unit)
{
    units.erase(std::remove(units.begin(), units.end(), unit), units.end());
}

/**
 * @brief Create units based on the specified unit types.
 *
 * Creates unit objects based on the provided unit types and adds them to the player's units.
 *
 * @param unitTypes The list of QString representing the types of units to create.
 */
void Player::createUnits(QList<QString> unitTypes){
    for(const QString &type:unitTypes){
        if(type=="infantry"){addUnits(new Infantry());}
        else if(type=="cavalry"){addUnits(new Cavalry());}
        else if(type=="artillery"){addUnits(new Artillery());}
    }
}
