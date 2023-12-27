#include "ai.h"
#include<QDebug>
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

    makeDefensiveMove();

}
void AI::makeAggressiveMove(vector<Unit*>& enemyUnits) {
    mode = AIMode::Aggressive;

    for (Unit* unit : units) {
        if (mode == AIMode::Aggressive) {
            Unit* closestEnemy = findClosestEnemy(unit, enemyUnits);
            if (closestEnemy) {
                QPointF target = closestEnemy->getPosition();
                unit->selected=true;
                unit->setTarget(target);
            } else {
                double randomX = rand() % 800;
                double randomY = rand() % 800;
                QPointF randomTarget(randomX, randomY);
                unit->setTarget(randomTarget);
            }
        }

        unit->rotate();
    }
}
void AI::makeDefensiveMove() {
    mode = AIMode::Defensive;

    for (Unit* unit : units) {
        if (mode == AIMode::Defensive) {
            Unit* closestFriend = findClosestFriend(unit, units);
            if (closestFriend && unit->needHelp) {

                QPointF target = unit->getPosition();
                closestFriend->selected = true;
                closestFriend->setTarget(target);

            } else {

            }
        }

        unit->rotate();
    }
}

Unit* AI::findClosestFriend(Unit* unit, const vector<Unit*>& setsOfUnits) {
    Unit* closestHelp = nullptr;
    double minDistance = std::numeric_limits<double>::max();

    for (Unit* help : setsOfUnits) {
        if (help == unit) {
            continue;
        }

        double distance = calculateDistance(help->getPosition(), unit->getPosition());

        if (distance < minDistance) {
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






