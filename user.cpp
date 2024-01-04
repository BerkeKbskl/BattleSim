#include "user.h"

/**
 * @brief Construct a new User object with the specified scenario.
 *
 * Initializes a User object with the given scenario, setting the color and deploying units.
 * Scenario will used to deploy units for.
 * @param scenario The scenario to associate with the user.
 */
User::User(Scenario scenario) {
    this->scenario=scenario;
    color=QColor(155,185,255);
    createUnits(scenario.getUnitsType(999));
}

/**
 * @brief Deploy units based on the specified scenario.
 *
 * Retrieves unit positions from the scenario and deploys units accordingly,
 * setting their positions and colors.
 *
 * @param scenario The scenario containing unit positions.
 */
void User::deployUnits(Scenario scenario) {


    QVector<QPointF>unitPositions=scenario.getUnitPositions(999);

    for(int i=0;i<unitPositions.size();i++){
        units[i]->setPosition({unitPositions[i].x(),unitPositions[i].y()});
         units[i]->setColor(this->color);
    }

}
