#ifndef AI_H
#define AI_H

#include "player.h"
class AI : public Player

{
   enum class AIMode {
        Aggressive,
        Defensive
    };

public:

    AI(Scenario scenario);
    Unit* findClosestFriend(Unit*, const QVector<Unit*>& setsOfUnits);

    void makeAggressiveMove(QVector<Unit*>& enemyUnits);
    void makeDefensiveMove();
    void deployUnits(Scenario scenario) override;
    void setMode(AIMode mode);
    void turnTowardEnemy(QVector<Unit*>& enemyUnits);
    void switchMode();
    Unit* findClosestEnemy(Unit* unit, const QVector<Unit*>& enemyUnits) ;
    double calculateDistance(const QPointF& point1, const QPointF& point2) ;

    void makeMove(QVector<Unit *> enemyUnits, QVector<Obstacle *> obstacles);
private:
    AIMode mode;
    bool isFirstMove;

};


#endif // AI_H
