#include "user.h"
#include <iostream>

User::User()
{
    color = Qt::blue;
}

void User::deployUnits(Scenario scenario) {


    vector<QPointF>unitPositions=scenario.getUserUntisPositions();
    for(int i=0;i<unitPositions.size();i++){
        units[i]->setPosition({unitPositions[i].x(),unitPositions[i].y()});
        units[i]->color = this->color;
    }

}
