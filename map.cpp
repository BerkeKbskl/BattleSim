// map.cpp
#include "map.h"
#include "river.h"
#include "swamp.h"

#define WW 1366
#define WH 768

Map::Map(Scenario scenario)
    : width(WW)
    , height(WH)
    , QRect(0, 0, WW, WH)
    , mapImage(scenario.getMapImage())
{
    // 2 Rivers
    for (int i = 0; i < 1; i++) {
        obstacles.push_back(new River({scenario.getObstaclePositions()}));
        // to be imported from scenarios themselves
    }
    /*
    for (int i = 0; i < 1; i++) {
        // the last item should be same as in first as it needs connection.
        obstacles.push_back(new Swamp({scenario.getObstaclePositions()}));

        // to be imported from scenarios themselves
    }*/
}

void Map::draw(QPainter *painter)
{

    painter->drawImage(*this, mapImage);


    for (Obstacle *obstacle : obstacles) {
        obstacle->draw(painter);
    }
}
