#ifndef UNIT_H
#define UNIT_H

#include "obstacle.h"
#include <QRect>
#include <QPainter>

/**
 * @brief The Unit class represents a basic unit in a game scenario.
 *
 * This class provides functionality for managing the position, movement,
 * and other properties of a game unit. It serves as a base class for more
 * specialized unit types.
 */
class Unit
{
public:

    /**
     * @brief Constructor for the Unit class.
     * @param x The initial x-coordinate of the unit.
     * @param y The initial y-coordinate of the unit.
     * @param width The width of the unit.
     * @param height The height of the unit.
     */
    Unit(int x = 1000, int y = 1000, double width = 39, double height = 24);

    /**
     * @brief Stops the unit, halting any ongoing movement.
     */
    void stop();

    /**
     * @brief Selects or deselects the unit based on the provided point.
     * @param point The point to check for unit selection.
     * @return True if the unit is selected, false otherwise.
     */
    bool selectUnit(const QPointF point);

    /**
     * @brief Sets the position of the unit.
     * @param v The new position of the unit.
     */
    void setPosition(const QPointF v);

    /**
     * @brief Sets the target position for the unit to move towards.
     * @param point The target position.
     */
    void setTarget(const QPointF point);

    /**
     * @brief Moves the unit towards its target position respect to the its speed.
     * @note Manhattan distance is the total lenght to overcome for the unit, if it is greater then speed it stops means that it arrived to the point.
     */
    void moveTo();

    /**
     * @brief Sets the selection status of the unit.
     * @param exp True if the unit is selected, false otherwise.
     */
    void setSelection(bool exp);

    /**
     * @brief Gets the current position of the unit.
     * @return The current position of the unit.
     */
    QPointF getPosition() const;

    /**
     * @brief Gets the path for the next movement step.
     * @note Path is the term for shape of unit.
     * @return The path for the next movement step.
     */
    QPainterPath getNextPath() const;

    /**
     * @brief Gets the current movement path of the unit.
     * @note Path is the term for shape of unit.
     * @return The current movement path of the unit.
     */
    QPainterPath getCurrentPath() const;

    /**
     * @brief Gets the attack collider for the unit.
     * @return The attack collider for the unit.
     */
    virtual QPainterPath getAttackCollider() const;

    /**
     * @brief Attacks an enemy unit.
     * @param enemy The enemy unit to be attacked.
     * @return The damage dealt to the enemy.
     */
    virtual int attack(Unit& enemy);

    /**
     * @brief Sets the color of the unit.
     * @param c The color to set.
     */
    void setColor(const QColor c);

    /**
     * @brief Draws the unit using the provided QPainter.
     * @param painter The QPainter to use for drawing.
     */
    virtual void draw(QPainter *painter);

    /**
     * @brief Moves the unit manually towards a specified point.
     * @param point The target point for manual movement.
     * @param border The border rect to constrain movement within.
     * @param obstacles A QVector containing pointers to obstacles in the game.
     * @param units A QVector containing pointers to other units in the game.
     */
    void manualMove(QPointF point, QRectF border, QVector<Obstacle*> obstacles, QVector<Unit*> units);

    /**
     * @brief Gets the current health of the unit.
     * @return The current health of the unit.
     */
    double getHealth() const;

    ~Unit();
protected:
    double angle; ///< Angle of unit in the plane.
    QColor color;
    QPointF target;///< Target point to move.
    QPointF center;
    QImage img;
    double attackPower;
    double health;///< Health of the unit. Dies if it is 0.
    double maxHealth;
    double speed;
    double defensePower;
    bool selected;
    bool movable;
    double width,height;

private:
    
};

#endif // UNIT_H
