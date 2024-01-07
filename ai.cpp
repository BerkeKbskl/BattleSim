#include <cmath>
#include <QPainterPath>
#include <QPointF>
#include <QVector>
#include <float.h>
#include "ai.h"
#include "qvectornd.h"

/**
 * @brief Calculate the square distance between two QPointF points.
 * @param p1 The first QPointF point.
 * @param p2 The second QPointF point.
 * @return The square distance between p1 and p2.
 */

double AI::squareDistanceTo(const QPointF& p1, const QPointF& p2) {
    double dx = p2.x() - p1.x();
    double dy = p2.y() - p1.y();
    return dx * dx + dy * dy;
}

/**
 * @brief Normalize the given QPointF vector.
 * @param v The QPointF vector to be normalized.
 */

void AI::normalize(QPointF& v) {
    double length = std::sqrt(v.x() * v.x() + v.y() * v.y());
    if (length != 0.0) {
        v.setX(v.x() / length);
        v.setY(v.y() / length);
    }
}

/**
 * @brief Find the closest point on a QPainterPath to a given QPointF point.
 * @param point The target point.
 * @param path The QPainterPath to find the closest point on.
 * @return The closest point on the path to the given point.
 */

QPointF AI::closestPointOnPath(const QPointF &point, const QPainterPath &path)
{
    if (path.isEmpty())
        return point;

    auto vec = QVector2D(point);
    auto poly = path.toFillPolygon();
    float d, minDist = FLT_MAX;
    QVector2D p, q, v, u, minVec;

    for (int k=0; k < poly.count() - 1; k++)
    {
        p = QVector2D(poly.at(k));
        if (k == poly.count() - 1)
            k = -1;
        q = QVector2D(poly.at(k+1));
        v = q - p;
        u = v.normalized();
        d = QVector2D::dotProduct(u, vec - p);

        if (d < 0.0f) {
            d = (vec - p).lengthSquared();

            if (d < minDist)
            {
                minDist = d;
                minVec = p;
            }
        }
        else if (d*d > v.lengthSquared())
        {
            d = (vec - q).lengthSquared();

            if (d < minDist)
            {
                minDist = d;
                minVec = q;
            }
        }
        else {
            u *= d;
            u += p;
            d = (vec - u).lengthSquared();

            if (d < minDist)
            {
                minDist = d;
                minVec = u;
            }
        }
    }

    if (minDist >= FLT_MAX)
        return point;

    return minVec.toPointF();
}

/**
 * @brief Calculate the repulsion force from an obstacle at the specified point.
 * @param x The x-coordinate of the point.
 * @param y The y-coordinate of the point.
 * @param obstaclePath The QPainterPath representing the obstacle.
 * @return The repulsion force vector.
 */

QPointF AI::getRepulsionForce(double x, double y, const QPainterPath& obstaclePath) {
    QPointF closestPoint = closestPointOnPath(QPointF(x, y), obstaclePath);
    double closestDist = squareDistanceTo(QPointF(x, y), closestPoint);

    double magnitude = 5.0 / closestDist;  // Adjust the magnitude as needed
    QPointF direction(x - closestPoint.x(), y - closestPoint.y());
    normalize(direction);
    direction.setX(direction.x() * magnitude);
    direction.setY(direction.y() * magnitude);
    return direction;
}

/**
 * @brief Calculate the attraction force towards an enemy at the specified position.
 * @param x The x-coordinate of the point.
 * @param y The y-coordinate of the point.
 * @param enemyPosition The position of the enemy.
 * @return The attraction force vector.
 */

QPointF AI::getAttractionForce(double x, double y, const QPointF& enemyPosition) {
    double distance = squareDistanceTo(QPointF(x, y), enemyPosition);

    double magnitude = 20 / distance;  // You might need to adjust the magnitude
    QPointF direction(enemyPosition.x() - x, enemyPosition.y() - y);
    normalize(direction);
    direction.setX(direction.x() * magnitude);
    direction.setY(direction.y() * magnitude);

    return direction;
}

/**
 * @brief Calculate the repulsion force from a friend at the specified position.
 * @param x The x-coordinate of the point.
 * @param y The y-coordinate of the point.
 * @param friendPosition The position of the friend unit.
 * @return The repulsion force vector.
 */

QPointF AI::getFriendForce(double x, double y, const QPointF& friendPosition) {

    double distance = squareDistanceTo(QPointF(x, y), friendPosition);
    double magnitude = 12120 / (distance * distance);  // You might need to adjust the magnitude
    QPointF direction(x-friendPosition.x(), y-friendPosition.y());
    normalize(direction);
    direction.setX(direction.x() * magnitude);
    direction.setY(direction.y() * magnitude);
    return direction;
}

/**
 * @brief Compute the vector field for a given unit based on surrounding obstacles, enemies, and friends.
 * @param unit The unit for which the vector field is computed.
 * @param obstacles Vector of obstacle pointers.
 * @param enemies Vector of enemy unit pointers.
 * @param friends Vector of friend unit pointers.
 * @return The resulting vector field for the unit.
 */

QPointF AI::computeVectorField(Unit* unit, const QVector<Obstacle*>& obstacles,
                           const QVector<Unit*>& enemies,
                           const QVector<Unit*>& friends) {
    QPointF repulsionForce(0, 0);
    QPointF attractionForce(0, 0);
    QPointF friendForce(0, 0);

    // Precompute the position of the unit outside the loops
    double unitX = unit->getPosition().x();
    double unitY = unit->getPosition().y();

    for (const auto& obstacle : obstacles) {
        QPointF obstacleForce = getRepulsionForce(unitX, unitY, obstacle->getPath());
        repulsionForce += obstacleForce;
    }

    for (const auto& enemy : enemies) {
        QPointF enemyForce = getAttractionForce(unitX, unitY, enemy->getPosition());
        attractionForce += enemyForce;
    }

    for (const auto& friendUnit : friends) {
        if (friendUnit != unit) {
            QPointF friendForce2 = getFriendForce(unitX, unitY, friendUnit->getPosition());
            friendForce += friendForce2;
        }
    }

    return repulsionForce + attractionForce + friendForce;
}

/**
 * @brief Constructor for the AI class.
 * @param scenario The scenario for which the player choose for play.
 */

AI::AI(Scenario scenario) {
    this->scenario = scenario;
    createUnits(scenario.getUnitsType(0));
    color = QColor(255, 155, 155);
}

/**
 * @brief Make a move for the AI-controlled units.
 * @param enemyUnits Vector of enemy unit pointers.
 * @param obstacles Vector of obstacle pointers.
 */

void AI::makeMove(QVector<Unit*> enemyUnits, QVector<Obstacle*> obstacles) {
    for (Unit* unit : getUnits()) {
        // Compute the vector field for the unit based on surrounding obstacles and enemies
        QPointF field = 20000 * computeVectorField(unit, obstacles, enemyUnits, this->getUnits());

        unit->setSelection(true);  // Assuming this is the selection logic
        unit->setTarget(unit->getPosition() + field);

    }
}

/**
 * @brief Deploy units to their initial positions in the scenario.
 * @param scenario The scenario containing the initial positions.
 */

void AI::deployUnits(Scenario scenario) {

    QVector<QPointF>unitPositions=scenario.getUnitPositions(0);
    for(int i=0;i<unitPositions.size();i++){
        units[i]->setPosition({unitPositions[i].x(),unitPositions[i].y()});
        units[i]->setColor(this->color);
    }

}
