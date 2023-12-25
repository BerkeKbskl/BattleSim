#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QPainterPath>
#include <QRect>
#include <QPainter>
#include <QTransform>

class Obstacle
{
public:
    Obstacle();
    void draw(QPainter* painter);
    QPainterPath shape;

protected:
    QColor color;

};

#endif // OBSTACLE_H
