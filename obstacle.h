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
    virtual void draw(QPainter* painter);
    QPainterPath shape;


protected:

};

#endif // OBSTACLE_H