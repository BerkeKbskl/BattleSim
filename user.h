#ifndef USER_H
#define USER_H

#include"player.h"

class User:public Player
{
public:
    User(Scenario scenario);
    void deployUnits(Scenario ) override;
};

#endif // USER_H
