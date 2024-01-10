#ifndef SWAMP_H
#define SWAMP_H

#include "obstacle.h"
#include <QPointF>

/**
 * @brief The Swamp class represents a swamp obstacle in a game scenario.
 *
 * This class is derived from the base Obstacle class and introduces specific
 * functionality for creating a swamp obstacle, including generating a smooth path
 * based on provided points.
 */
class Swamp : public Obstacle
{
public:

    /**
     * @brief Constructor for the Swamp class.
     * @param points The points defining the shape of the swamp obstacle.
     */
    Swamp(const QVector<QPointF>& points);

    /**
     * @brief Generates a smooth path for the swamp obstacle based on provided points.
     * @param points The points defining the shape of the swamp obstacle.
     * @return A QPainterPath representing the smooth path of the swamp obstacle.
     */
    QPainterPath generateSmoothPath(const QVector<QPointF>& points);

    /**
     * @brief Overrides the base class draw function to provide custom drawing for the swamp obstacle.
     * @param painter The QPainter to use for drawing.
     */
    void draw(QPainter* painter) override;

    /**
     * @brief Overrides the base class function to provide the path of the swamp obstacle.
     * @return A QPainterPath representing the path of the swamp obstacle.
     */
    QPainterPath getPath() const override;

private:
    QPainterPath path; ///< The QPainterPath representing the path of the swamp obstacle.

};

#endif // SWAMP_H
