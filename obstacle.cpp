#include "obstacle.h"

Obstacle::Obstacle()
{
    // Additional initialization if needed
}


void Obstacle::draw(QPainter* painter)
{
    painter->save();
    painter->setBrush(QBrush(QColor(255,255,155)));
    painter->drawPolygon(shape);
    painter->restore();
}


