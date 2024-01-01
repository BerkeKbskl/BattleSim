// map.cpp
#include "map.h"
#include "river.h"
#include "swamp.h"

#define WW 1366
#define WH 768

/**
 * @brief Construct a new Map object based on the specified scenario.
 *
 * Initializes a Map object with the specified width, height, map image, and obstacles
 * extracted from the provided scenario.
 *
 * @param scenario The scenario containing information about the map and obstacles.
 */
Map::Map(Scenario scenario)
    : width(WW)
    , height(WH)
    , QRect(0, 0, WW, WH)
    , mapImage(scenario.getMapImage())
{
    for (int i = 0; i < scenario.getObstacleTypes().size(); i++) {
        QString type = scenario.getObstacleTypes()[i];
        if (type == "river") { obstacles.push_back(new River(scenario.getObstaclePositions()[i]));}
        else if (type == "swamp") { obstacles.push_back(new Swamp(scenario.getObstaclePositions()[i]));}
    }

}

void Map::draw(QPainter *painter)
{
    painter->drawImage(*this, mapImage);
    for (Obstacle *obstacle : obstacles) {
        obstacle->draw(painter);
    }
}

QVector<Obstacle*> Map::getObstacles()
{
    return obstacles;
}
