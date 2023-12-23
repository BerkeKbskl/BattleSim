#ifndef USER_H
#define USER_H

#include"player.h"

class User:public Player
{
public:
    User();
    void deployUnits(Scenario ) override;
};

#endif // USER_H
