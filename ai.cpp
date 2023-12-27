#include "ai.h"
#include <iostream>

AI::AI(Scenario scenario) {

    scenario=scenario;
    createUnits(scenario.getAIUnitsType());
    color = QColor(255,155,155);
}
void AI::setMode(AIMode mode) {
    this->mode = mode;
}

void AI::switchMode() {
    if (mode == AIMode::Aggressive) {
        mode = AIMode::Defensive;
    } else {
        mode = AIMode::Aggressive;
    }
}


void AI::makeMove(vector<Unit*> enemyUnits) {
    mode = AIMode::Aggressive;
    for (Unit *unit : units) {


        // Find the closest enemy unit

        if(mode == AIMode::Aggressive){
        Unit* closestEnemy = findClosestEnemy(unit, enemyUnits);
        if (closestEnemy) {
            // Move towards the closest enemy
            QPointF target = closestEnemy->getPosition();

            cout << target.x() << "," << target.y() << endl;
            unit->selected = true;
            unit->setTarget(target);
        } else {
            // If no enemies are present, move towards a random point on the map
            double randomX = rand() % 800;
            double randomY = rand() % 800;
            QPointF randomTarget(randomX, randomY);
            unit->setTarget(randomTarget);
        }


        }else if(mode == AIMode::Defensive){
        Unit* closestFriend = findClosestFriend(unit, units);
        if (closestFriend) {
            // Move towards the closest enemy
            QPointF target = closestFriend->getPosition();

            cout << target.x() << "," << target.y() << endl;
            unit->selected = true;
            unit->setTarget(target);
        }
        }

        unit->rotate();
    }
}

Unit* AI::findClosestFriend(Unit* unit, const vector<Unit*>& setsOfUnits) {
    Unit* closestHelp = nullptr;
    double minDistance = std::numeric_limits<double>::max();

    for (Unit* help : setsOfUnits) {
        if(help == unit){
            continue;
        }
        double distance = calculateDistance(unit->getPosition(), help->getPosition());

        if (distance < minDistance && help->isHelpNeed()) {
            help->needHelp=true; // will be developed further.
            minDistance = distance;
            closestHelp = help;
        }
    }

    return closestHelp;
}
Unit* AI::findClosestEnemy(Unit* unit, const vector<Unit*>& enemyUnits) {
    Unit* closestEnemy = nullptr;
    double minDistance = std::numeric_limits<double>::max();

    for (Unit* enemy : enemyUnits) {
        double distance = calculateDistance(unit->getPosition(), enemy->getPosition());

        if (distance < minDistance) {
            minDistance = distance;
            closestEnemy = enemy;
        }
    }

    return closestEnemy;
}


double AI::calculateDistance(const QPointF& point1, const QPointF& point2) {
    double dx = point2.x() - point1.x();
    double dy = point2.y() - point1.y();
    return std::sqrt(dx * dx + dy * dy);
}




void AI::deployUnits(Scenario scenario) {

    vector<QPointF>unitPositions=scenario.getAIUntisPositions();
    for(int i=0;i<unitPositions.size();i++){
        units[i]->setPosition({unitPositions[i].x(),unitPositions[i].y()});
        units[i]->color = this->color;
    }

}






