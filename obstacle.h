#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QPainterPath>
#include <QRect>
#include <QPainter>
#include <QTransform>

/**
 * @brief The Obstacle class represents a generic obstacle in a game scenario.
 *
 * This class provides basic functionality for drawing obstacles and obtaining their paths.
 */
class Obstacle
{
public:

    /**
     * @brief Constructor for the Obstacle class.
     */
    Obstacle();

    /**
     * @brief Virtual function to draw the obstacle using the provided QPainter.
     * @param painter The QPainter to use for drawing.
     */
    virtual void draw(QPainter* painter);

    /**
     * @brief Pure virtual function to get the path of the obstacle.
     * @return A QPainterPath representing the path of the obstacle.
     */
    virtual QPainterPath getPath() const = 0;

};

#endif // OBSTACLE_H
