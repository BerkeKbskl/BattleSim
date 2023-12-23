#include "obstacle.h"

Obstacle::Obstacle()

{
    // Additional initialization if needed
}




void Obstacle::draw(QPainter* painter)
{
    // Draw only the outline of the rotated rectangle as a red line
    painter->save();
    painter->setBrush(QBrush(Qt::blue));
    painter->drawPolygon(shape);
    painter->restore();

}


