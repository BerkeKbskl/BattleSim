// river.cpp

#include "river.h"
#include <QDebug>

River::River(const QList<QPointF>& points)
{
    shape = bezierPathFromPoints(points);
    color = Qt::blue;  // Set the river color (you can change it as needed)
}

QPainterPath River::bezierPathFromPoints(const QList<QPointF>& points)
{
    QPainterPath path;

    path.moveTo(points.first());

    for (int i = 0; i < points.size(); i += 2) {
        QPointF controlPoint1 = points.at(i);
        QPointF controlPoint2, endPoint;

        if (i + 1 < points.size()) {
            controlPoint2 = points.at(i + 1);
        } else {
            controlPoint2 = points.first();  // Wrap around to the first point
        }

        if (i + 2 < points.size()) {
            endPoint = points.at(i + 2);
        } else {
            endPoint = points.first();  // Wrap around to the first point
        }

        path.cubicTo(controlPoint1, controlPoint2, endPoint);
    }


    // Connect the last point to the first point to close the path
    path.lineTo(points.first());

    return path;
}
