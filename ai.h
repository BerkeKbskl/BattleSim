#ifndef AI_H
#define AI_H

#include "player.h"
class AI : public Player

{
public:
    AI(Scenario scenario);
    void makeMove();
    void deployUnits(Scenario scenario) override;

    void makeMove(vector<Unit*> enemyUnits);

    Unit* findClosestEnemy(Unit* unit, const vector<Unit*>& enemyUnits) ;

    double calculateDistance(const QPointF& point1, const QPointF& point2) ;




private:
};

#endif // AI_H
