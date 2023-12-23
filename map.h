// map.h
#ifndef MAP_H
#define MAP_H

#include "obstacle.h"
#include <QObject>
#include <QRect>
#include <QPainter>

class Map : public QObject, public QRect
{
    Q_OBJECT

public:
    Map(QImage );
    void draw(QPainter* painter);
    std::vector<Obstacle*> obstacles;


private:
    QImage mapImage;
    int width;
    int height;
};

#endif // MAP_H
