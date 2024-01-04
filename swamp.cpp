#include "swamp.h"

/**
 * @brief Construct a new Swamp object with the specified points.
 *
 * Initializes a closed collider object with a
 * smooth path generated from the given points.
 *
 * @param points The points defining the shape of the collider.
 */
Swamp::Swamp(const QVector<QPointF>& points)
    : path(generateSmoothPath(points))
{
}

/**
 * @brief Generate a smooth QPainterPath from the specified points.
 *
 * This function takes a set of points and generates a smooth QPainterPath representing
 * the shape of the swamp. The smooth path is created using cubic Bezier curves.
 *
 * @param points The points defining the shape of the swamp.
 * @return A smooth QPainterPath representing the swamp shape.
 */
QPainterPath Swamp::generateSmoothPath(const QVector<QPointF>& points)
{
    qreal factor = 0.30;
    QPainterPath path(points[0]);

    QPointF cp1;

    for (int p = 1; p < points.size() - 1; ++p) {
        QLineF source(points[p - 1], points[p]);
        QLineF target(points[p], points[p + 1]);

        qreal targetAngle = target.angleTo(source);
        qreal angle;

        if (targetAngle > 180)
            angle = fmod((source.angle() + source.angleTo(target) / 2), 360);
        else
            angle = fmod((target.angle() + target.angleTo(source) / 2), 360);

        QLineF revTarget = QLineF::fromPolar(source.length() * factor, angle + 180).translated(points[p]);
        QPointF cp2 = revTarget.p2();

        if (p == 1)
            path.quadTo(cp2, points[p]);
        else
            path.cubicTo(cp1, cp2, points[p]);

        QLineF revSource = QLineF::fromPolar(target.length() * factor, angle).translated(points[p]);
        cp1 = revSource.p2();
    }

    // the final curve, that joins to the last point
    path.quadTo(cp1, points.last());
    path.cubicTo(points.last(), points.first(),points.first());
    path.closeSubpath();

    return path;

}

QPainterPath Swamp::getPath() const
{
    return path;
}

void Swamp::draw(QPainter* painter)
{
    //painter->setRenderHint(QPainter::Antialiasing, true);
    //painter->setPen(QPen(Qt::blue, 2));
    //painter->setBrush(Qt::blue);
    //painter->drawPath(path);
}




