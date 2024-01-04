#include "river.h"

/**
 * @brief Construct a new River object with the specified points.
 *
 * Initializes a River object with a smooth path generated from the given points.
 *
 * @param points The points defining the shape of the river.
 */
River::River(const QVector<QPointF>& points)
    : path(generateSmoothPath(points))
{
}

/**
 * @brief Generate a smooth QPainterPath from the specified points.
 *
 * This function takes a set of points and generates a smooth QPainterPath representing
 * the shape of the river. The smooth path is created using cubic Bezier curves.
 *
 * @param points The points defining the shape of the river.
 * @return A smooth QPainterPath representing the river shape.
 */
QPainterPath River::generateSmoothPath(const QVector<QPointF>& points)
{
    qreal factor = 0.40; // Adjust the factor as needed
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
    path.quadTo(cp1, points.back());

    QPainterPathStroker stroker;
    stroker.setWidth(70);
    return stroker.createStroke(path);
}


void River::draw(QPainter* painter)
{
    painter->setRenderHint(QPainter::Antialiasing, true);

    // Create a linear gradient along the river path
    //QLinearGradient gradient(path.boundingRect().topLeft(), path.boundingRect().bottomRight());
    //gradient.setColorAt(0, Qt::blue);
    //gradient.setColorAt(1, Qt::darkBlue);

    //Set the gradient as the brush for the river
    //painter->setBrush(gradient);
    //painter->setPen(QPen(Qt::blue, 2));
    //painter->drawPath(path);
}

QPainterPath River::getPath() const
{
    return path;
}
