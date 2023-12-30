#ifndef ARTILLERY_H
#define ARTILLERY_H

#include "unit.h"

class Artillery : public Unit
{
public:
    Artillery();
    bool shoot();
    int attack(Unit&) override;
    void draw(QPainter*) override;
    QPainterPath getAttackCollider() const override;

private:
    int ammo;

};

#endif // ARTILLERY_H
