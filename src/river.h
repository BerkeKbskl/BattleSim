// river.h
#ifndef RIVER_H
#define RIVER_H

#include "obstacle.h"
#include <QVector>
#include <QPointF>
#include <QPainterPath>

/**
 * @brief The River class represents a river obstacle in a game scenario.
 *
 * This class is derived from the base Obstacle class and introduces specific
 * functionality for creating a river obstacle, including generating a smooth path
 * based on provided points.
 */
class River : public Obstacle
{
public:

    /**
     * @brief Constructor for the River class.
     * @param points The points defining the shape of the river obstacle.
     */
    River(const QVector<QPointF>& points);

    /**
     * @brief Generates a smooth path for the river obstacle based on provided points.
     * @param points The points defining the shape of the river obstacle.
     * @return A QPainterPath representing the smooth path of the river obstacle.
     */
    static QPainterPath generateSmoothPath(const QVector<QPointF>& points);

    /**
     * @brief Overrides the base class draw function to provide custom drawing for the river obstacle.
     * @param painter The QPainter to use for drawing.
     */
    void draw(QPainter* painter) override;

    /**
     * @brief Overrides the base class function to provide the path of the river obstacle.
     * @return A QPainterPath representing the path of the river obstacle.
     */
    QPainterPath getPath() const override;

private:
    QPainterPath path; ///< The QPainterPath representing the path of the river obstacle.

};

#endif // RIVER_H
