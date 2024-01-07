// map.cpp
#include "map.h"
#include "river.h"
#include "swamp.h"


/**
 * @brief Construct a new Map object based on the specified scenario.
 *
 * Initializes a Map object with the specified width, height, map image, and obstacles
 * extracted from the provided scenario.
 *
 * @param scenario The scenario containing information about the map and obstacles.
 */
Map::Map(Scenario scenario, Settings settings)
    :
    QRect(0, 0,settings.getScreenSize().width(),settings.getScreenSize().height())
    , mapImage(scenario.getMapImage())
    , scenario(scenario)
{
    for (int i = 0; i < scenario.getObstacleTypes().size(); i++) {
        QString type = scenario.getObstacleTypes()[i];
        if (type == "river") { obstacles.push_back(new River(scenario.getObstaclePositions()[i]));}
        else if (type == "swamp") { obstacles.push_back(new Swamp(scenario.getObstaclePositions()[i]));}
    }

}

void Map::draw(QPainter *painter)
{
    //double scale=scenario.getScale();
   // if(scale!=1.0){setSize(QSize(scale*width,scale*height));}
    painter->drawImage(*this, mapImage);
    for (Obstacle *obstacle : obstacles) {
        obstacle->draw(painter);
    }
}

QVector<Obstacle*> Map::getObstacles()
{
    return obstacles;
}
