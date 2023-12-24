#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QRect>
#include <QPainter>
#include <QTransform>

class Obstacle
{
public:
    Obstacle();
    void draw(QPainter* painter);
    QPolygonF shape;


protected:
    QColor color;

};

#endif // OBSTACLE_H
