// river.h
#ifndef RIVER_H
#define RIVER_H

#include "obstacle.h"
#include <QVector>
#include <QPointF>
#include <QPainterPath>

class River : public Obstacle
{
public:
    River(const QVector<QPointF>& points);

    static QPainterPath generateSmoothPath(const QVector<QPointF>& points);

    void draw(QPainter* painter) override;

private:
    QPainterPath path;
};

#endif // RIVER_H