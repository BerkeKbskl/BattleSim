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
    Unit* findClosestFriend(Unit*, const vector<Unit*>& setsOfUnits);

    void makeAggressiveMove(vector<Unit*>& enemyUnits);
    void makeDefensiveMove();
    void deployUnits(Scenario scenario) override;
    void setMode(AIMode mode);
    void switchMode();
    void makeMove(vector<Unit*> enemyUnits);

    Unit* findClosestEnemy(Unit* unit, const vector<Unit*>& enemyUnits) ;

    double calculateDistance(const QPointF& point1, const QPointF& point2) ;




private:
    AIMode mode;

};


#endif // AI_H
