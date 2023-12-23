#include "ai.h"
#include <iostream>

AI::AI(Scenario scenario) {
    this->scenario=scenario;
    createUnits(scenario.getAIUnitsType());
    color = Qt::black;
}


void AI::deployUnits(Scenario scenario) {

    vector<QPointF>unitPositions=scenario.getAIUntisPositions();
    for(int i=0;i<unitPositions.size();i++){
        units[i]->setPosition({unitPositions[i].x(),unitPositions[i].y()});
        units[i]->color = this->color;
    }

}

void AI::makeMove() {
    // when should this be triggered?
}




