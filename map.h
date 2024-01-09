// map.h
#ifndef MAP_H
#define MAP_H

#include "Scenario.h"
#include "obstacle.h"
#include "settings.h"
#include <QObject>
#include <QRect>
#include <QPainter>

/**
 * @brief The Map class represents the game map in a scenario.
 *
 * This class inherits from QRect and QObject, providing functionality for drawing
 * the map and accessing information about obstacles on the map.
 */
class Map : public QObject, public QRect
{
    Q_OBJECT

public:

    /**
     * @brief Constructor for the Map class.
     * @param scenario The game scenario associated with the map.
     * @param settings The settings for the game map.
     */
    Map(Scenario scenario, Settings settings);

    /**
     * @brief Draws the map using the provided QPainter.
     * @param painter The QPainter to use for drawing.
     */
    void draw(QPainter* painter);

    /**
     * @brief Gets a QVector of obstacle pointers representing obstacles on the map.
     * @return A QVector of Obstacle pointers.
     */
    QVector<Obstacle*> getObstacles();

private:
    QImage mapImage;
    QVector<Obstacle*> obstacles;
    int width = 0;
    int height = 0;
    Scenario scenario;

};

#endif // MAP_H

