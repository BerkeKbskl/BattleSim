#ifndef USER_H
#define USER_H

#include"player.h"
/**
 * @brief The User class represents a user-controlled player in a game scenario.
 *
 * This class is derived from the Player class and is responsible for implementing
 * the logic for user-controlled players, including unit deployment.
 */
class User : public Player
{
public:
    /**
     * @brief Constructor for the User class.
     * @param scenario The game scenario in which the user player operates.
     */
    User(Scenario scenario);
    /**
     * @brief Deploys units for the user player to the map in the specified scenario.
     * @param scenario The game scenario in which the user player deploys units.
     */
    void deployUnits(Scenario) override;
};

#endif // USER_H
