#ifndef SWAMP_H
#define SWAMP_H

#include "obstacle.h"
#include <QPointF>

class Swamp : public Obstacle
{
public:
    Swamp(const QVector<QPointF>& points);
    QPainterPath generateSmoothPath(const QVector<QPointF>& points);
    void draw(QPainter* painter) override;
    QPainterPath getPath() const override;

private:
    QPainterPath path;
};

#endif // SWAMP_H
