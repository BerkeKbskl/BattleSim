// map.h
#ifndef MAP_H
#define MAP_H

#include "Scenario.h"
#include "obstacle.h"
#include "settings.h"
#include <QObject>
#include <QRect>
#include <QPainter>

class Map : public QObject, public QRect
{
    Q_OBJECT

public:
    Map(Scenario scenario,Settings settings);
    void draw(QPainter* painter);
    QVector<Obstacle*> getObstacles();

private:
    QImage mapImage;
    QVector<Obstacle*> obstacles;
    int width=0;
    int height=0;
    Scenario scenario;
};

#endif // MAP_H
