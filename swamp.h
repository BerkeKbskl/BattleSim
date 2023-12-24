#ifndef SWAMP_H
#define SWAMP_H

#include "obstacle.h"
#include <QPointF>

class Swamp : public Obstacle
{
public:
    Swamp(QPointF,QPointF,QPointF,QPointF);

};

#endif // SWAMP_H
