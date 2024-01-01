#include "ai.h"
#include<QDebug>
#include <iostream>

AI::AI(Scenario scenario) {

    scenario=scenario;
    createUnits(scenario.getUnitsType(0));
    color = QColor(255,155,155);
    isFirstMove = true;

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


void AI::makeMove(QVector<Unit*> enemyUnits) {
    int totalAllyHealth=0;
    int totalEnemyHealth=0;
    if (isFirstMove) {

        int randomMode = rand() % 2;

        if (randomMode == 0) {
            mode = AIMode::Aggressive;
        } else {
            mode = AIMode::Defensive;
        }
        isFirstMove = false;
    }
    for (Unit* unit : units) {
        if(unit)
            totalAllyHealth += unit->getHealth();
    }
    for(Unit* unit : enemyUnits){
        if(unit)
            totalEnemyHealth += unit->getHealth();
    }
    if(totalAllyHealth>totalEnemyHealth*0.6){
        mode = AIMode::Aggressive;
    }else{
        mode = AIMode::Defensive;
    }

    if (mode == AIMode::Aggressive) {
        makeAggressiveMove(enemyUnits);
    } else {
        //Defensive move
        turnTowardEnemy(enemyUnits);
        //makeDefensiveMove();

    }

}
void AI::turnTowardEnemy(QVector<Unit*>& enemyUnits){
    for (Unit* unit : units) {
        Unit* closestEnemy = findClosestEnemy(unit, enemyUnits);
        QPointF target = closestEnemy->getPosition();
        unit->setSelection(true);
        unit->setTarget(target);
        unit->stop();
        makeDefensiveMove();
    }
}


void AI::makeAggressiveMove(QVector<Unit*>& enemyUnits) {
    mode = AIMode::Aggressive;

    for (Unit* unit : units) {
        if (mode == AIMode::Aggressive) {
            Unit* closestEnemy = findClosestEnemy(unit, enemyUnits);
            if (closestEnemy) {
                QPointF target = closestEnemy->getPosition();
                unit->setSelection(true);
                unit->setTarget(target);
            } else {
                double randomX = rand() % 800;
                double randomY = rand() % 800;
                QPointF randomTarget(randomX, randomY);
                unit->setTarget(randomTarget);
            }
        }


    }
}
void AI::makeDefensiveMove() {
    mode = AIMode::Defensive;

    for (Unit* unit : units) {
        if (mode == AIMode::Defensive) {
            Unit* closestFriend = findClosestFriend(unit, units);
            if (closestFriend && unit->needHelp) {

                QPointF target = unit->getPosition();
                closestFriend->setSelection(true);
                closestFriend->setTarget(target);

            } else {

            }
        }

    }
}

Unit* AI::findClosestFriend(Unit* unit, const QVector<Unit*>& setsOfUnits) {
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

Unit* AI::findClosestEnemy(Unit* unit, const QVector<Unit*>& enemyUnits) {
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

    QVector<QPointF>unitPositions=scenario.getUnitPositions(0);
    for(int i=0;i<unitPositions.size();i++){
        units[i]->setPosition({unitPositions[i].x(),unitPositions[i].y()});
        units[i]->setColor(this->color);
        // has to be deployed 180 degrees because they face the opposite way.
    }

}






