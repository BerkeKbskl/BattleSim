#ifndef AI_H
#define AI_H

#include "player.h"

/**
 * @brief The AI class represents an ai player in a game scenario.
 *
 * This class is inherits the Player class and it is responsible for implementing
 * the logic for opponent behaviours like development units, obstacle avoiding, find an enemy unit to attack.
 */

class AI : public Player

{

public:
    /**
     * @brief Constructor for the AI class.
     * @param scenario The game scenario in which the AI player operates.
     */
    AI(Scenario scenario);
    /**
     * @brief Deploys units for the AI player in the specified scenario.
     * @param scenario The game scenario in which the AI player deploys units.
     */
    void deployUnits(Scenario scenario) override;
    /**
     * @brief Makes move with all AI units according to positions of enemy units, obstacles and friendly units.
     * @note Uses vector fields for avoid obstacles and friendly units, it calculates all the vectors via distance.
     * @param enemyUnits A QVector containing pointers to enemy units.
     * @param obstacles A QVector containing pointers to obstacles in the game.
     */
    void makeMove(QVector<Unit *> enemyUnits, QVector<Obstacle *> obstacles);
    /**
     * @brief Computes the square of the distance between two points.
     * @param p1 The first point.
     * @param p2 The second point.
     * @return The square of the distance between p1 and p2.
     */
    double squareDistanceTo(const QPointF& p1, const QPointF& p2);
    /**
     * @brief Normalizes the given vector.
     * @param v The vector to be normalized.
     */
    void normalize(QPointF& v);
private:
    /**
     * @brief Finds the closest point on a path to the specified point.
     * @note Its finds the closest point to the river and swamp object.
     * @param point The target point.
     * @param path The QPainterPath to find the closest point on.
     * @return The closest point on the path to the specified point.
     */
    QPointF closestPointOnPath(const QPointF &point, const QPainterPath &path);
    /**
     * @brief Calculates the repulsion force from an obstacle at the specified position.
     * @param x X-coordinate of the point.
     * @param y Y-coordinate of the point.
     * @param obstaclePath The path representing the obstacle.
     * @return The repulsion force vector.
     */
    QPointF getRepulsionForce(double x, double y, const QPainterPath& obstaclePath);
    /**
     * @brief Calculates the attraction force towards an enemy at the specified position.
     * @param x X-coordinate of the point.
     * @param y Y-coordinate of the point.
     * @param enemyPosition The position of the enemy unit.
     * @return The attraction force vector.
     */
    QPointF getAttractionForce(double x, double y, const QPointF& enemyPosition);
    /**
     * @brief Calculates the friend force towards a friendly unit at the specified position.
     * @param x X-coordinate of the point.
     * @param y Y-coordinate of the point.
     * @param friendPosition The position of the friendly unit.
     * @return The friend force vector.
     */

    QPointF getFriendForce(double x, double y, const QPointF& friendPosition);
    /**
     * @brief Computes the vector field for a given unit based on the game state.
     * @note  This function puts all vectors together and calculates their resultant vector for each unit.
     * @param unit The AI-controlled unit.
     * @param obstacles A QVector containing pointers to obstacles in the game.
     * @param enemies A QVector containing pointers to enemy units.
     * @param friends A QVector containing pointers to friendly units.
     * @return The vector field indicating the direction of movement for the unit.
     */
    QPointF computeVectorField(Unit* unit, const QVector<Obstacle*>& obstacles,const QVector<Unit*>& enemies,const QVector<Unit*>& friends);



};


#endif // AI_H
