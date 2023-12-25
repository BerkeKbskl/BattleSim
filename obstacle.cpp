#include "obstacle.h"

Obstacle::Obstacle()
{
    // Additional initialization if needed
}


void Obstacle::draw(QPainter* painter)
{
    // Create a radial gradient from the center to the outer edges
    QPointF center = shape.boundingRect().center();
    QRadialGradient gradient(center, qMax(shape.boundingRect().width(), shape.boundingRect().height()) / 2);
    gradient.setColorAt(0, color.darker(60));
    gradient.setColorAt(1, color.darker(150));

    // Set the pen color and other rendering options
    painter->setPen(color.lighter(60));
    painter->setRenderHint(QPainter::Antialiasing, true);

    // Fill the shape with the gradient brush
    painter->setBrush(gradient);
    painter->drawPath(shape);
}






