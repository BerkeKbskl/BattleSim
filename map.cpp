// map.cpp
#include "map.h"
#include "river.h"
#include "swamp.h"

#define WW 1000
#define WH 1000

Map::Map(Scenario scenario)
    : width(WW)
    , height(WH)
    , QRect(0, 0, WW, WH)
    , mapImage(scenario.getMapImage())
{
    // 2 Rivers
    for (int i = 0; i < 1; i++) {
        obstacles.push_back(new River({ {127, 607}, {200, 526}, {384, 606},
                                {446, 531}, {530, 548}, {590, 368},{666, 666}
            ,{756, 581} }));

        // to be imported from scenarios themselves
    }
    /*
    for (int i = 0; i < 1; i++) {
        obstacles.push_back(new Swamp({ {497, 176}, {637, 104}, {692, 261},
                                {666, 355}, {583, 321},{400, 221} }));

        // to be imported from scenarios themselves
    }*/
}

void Map::draw(QPainter *painter)
{
    //painter->fillRect(0,0,WW,WH,Qt::gray);
    painter->setOpacity(0.3); // too distracting
    painter->drawImage(*this, mapImage);

    painter->setOpacity(1);
    for (Obstacle *obstacle : obstacles) {
        obstacle->draw(painter);
    }
}
