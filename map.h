// map.h
#ifndef MAP_H
#define MAP_H

#include "Scenario.h"
#include "obstacle.h"
#include <QObject>
#include <QRect>
#include <QPainter>

class Map : public QObject, public QRect
{
    Q_OBJECT

public:
    Map(Scenario scenario);
    void draw(QPainter* painter);
    std::vector<Obstacle*> getObstacles();

private:
    QImage mapImage;
    std::vector<Obstacle*> obstacles;
    int width;
    int height;
};

#endif // MAP_H
