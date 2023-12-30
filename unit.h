#ifndef UNIT_H
#define UNIT_H
#include "obstacle.h"
#include<QRect>
#include<QPainter>

using namespace std;

class Unit
{
public:

    Unit(int x = 1000, int y = 1000, double width = 50, double height = 25);
    void setPosition(QPointF v);
    void moveTo();
    void selectUnit(QPointF);
    bool isHelpNeed(); // for AI
    QPointF getPosition();
    virtual void draw(QPainter *);
    void rotate();
    QPolygonF getNextPoly();
    virtual QPolygonF getNextCollider();
    double getAngle();
    double getOrientation();
    QPointF target;
    void setCollisionState(int index);
    void setTarget(QPointF point);
    bool selected;
    double orientation;
    QColor color;

    QPolygonF shape;
    QPolygonF collider;
    bool needHelp;
    bool helpAssigned;
    virtual int attack(Unit& enemy);
    int health;

    double angle;

    QPainterPath getNextPath();
    QPainterPath getColliderBoundaries();
    QPainterPath getCurrentPath();
    void stop();
protected:

    QImage img;
    int attackPower;

    int speed;
    int moral;
    int defensePower;
    bool movable;
    int collisionState;
    double width,height; // SEE



private:


};

#endif // UNIT_H
