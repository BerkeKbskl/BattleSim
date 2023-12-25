// river.h

#ifndef RIVER_H
#define RIVER_H

#include "obstacle.h"
#include <QPointF>
#include <QPainterPath>

class River : public Obstacle
{
public:
    River(const QList<QPointF>& points);

private:
    QPainterPath bezierPathFromPoints(const QList<QPointF>& points);
};

#endif // RIVER_H
