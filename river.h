#ifndef RIVER_H
#define RIVER_H

#include "obstacle.h"
#include <QPointF>

class River : public Obstacle
{
public:
    River(QPointF,QPointF);

};

#endif // RIVER_H
