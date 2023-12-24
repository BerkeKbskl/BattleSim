// map.cpp
#include "map.h"
#include "river.h"
#include "swamp.h"

#define WW 1000
#define WH 1000

Map::Map(Scenario scenario)
    : width(WW),
    height(WH),
    QRect(0, 0, WW, WH),
    mapImage(scenario.getMapImage()) {

    // 2 Rivers
    for(int i=0;i<2;i++){
        obstacles.push_back(new River(
            {rand()%800+0.0,rand()%800+0.0},{rand()%800+0.0,rand()%800+0.0}));
        // to be imported from scenarios themselves
    }
    // 1 Swamp
    for(int i=0;i<1;i++){
        vector<double> randPt = {rand()%800+0.0,rand()%800+0.0};
        obstacles.push_back(new Swamp(
            {randPt[0],randPt[1]},
            {randPt[0]+0,randPt[1]+100},
            {randPt[0]+120,randPt[1]+100},
            {randPt[0]+120,randPt[1]}
            ));
        // to be imported from scenarios themselves
    }

    // test-map: to-do remove.

    mapImage.load(":images/images/map.jpg");

}

void Map::draw(QPainter* painter)
{
    //painter->fillRect(0,0,WW,WH,Qt::gray);
    painter->setOpacity(0.3); // too distracting
    painter->drawImage(*this,mapImage);

    painter->setOpacity(1);
    for(Obstacle* obstacle : obstacles){
        obstacle->draw(painter);
    }

}
