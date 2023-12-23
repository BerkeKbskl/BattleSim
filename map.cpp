// map.cpp
#include "map.h"
#include "river.h"

#define WW 1000
#define WH 1000

Map::Map(Scenario scenario)
    : width(WW),
    height(WH),
    QRect(0, 0, WW, WH),mapImage(scenario.getMapImage()) {


    for(int i=0;i<2;i++){
        obstacles.push_back(new River(
            {rand()%800+0.0,rand()%800+0.0},{rand()%800+0.0,rand()%800+0.0}));
    }

}

void Map::draw(QPainter* painter)
{   QRect map(0,0,WW,WH);
    painter->fillRect(0,0,WW,WH,Qt::gray);
    //painter->drawImage(map,mapImage);
    for(Obstacle* obstacle : obstacles){
        obstacle->draw(painter);
    }

}
