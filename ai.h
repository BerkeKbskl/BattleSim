#ifndef AI_H
#define AI_H

#include "player.h"
class AI : public Player

{
public:
    AI(Scenario scenario);
    void makeMove();
    void deployUnits(Scenario scenario) override;

private:
};

#endif // AI_H
