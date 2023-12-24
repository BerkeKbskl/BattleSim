#include "obstacle.h"

Obstacle::Obstacle()
{
    // Additional initialization if needed
}


void Obstacle::draw(QPainter* painter)
{
    painter->save();
    painter->setBrush(color);
    painter->setPen(color.lighter(60));
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->drawPolygon(shape);
    painter->restore();


}


