#ifndef UNIT_H
#define UNIT_H
#include "obstacle.h"
#include<QRect>
#include<QPainter>

using namespace std;

class Unit
{
public:

    Unit(int x = 1000, int y = 1000, double width = 25, double height = 50);
    void setPosition(vector<double> v);
    void moveTo();
    void selectUnit(QPoint);
    virtual void draw(QPainter *);
    void rotate(double degrees);
    QPolygonF getNextPoly();
    virtual QPolygonF getNextCollider();
    double getAngle();
    double getOrientation();
    vector<int> target;
    void setCollisionState(int index);
    void setTarget(QPoint point);
    bool selected;
    double orientation;
    QColor color;

    QPolygonF shape;
    QPolygonF collider;

    QImage img;
    virtual int attack(Unit& enemy);
    int health;
protected:


    double newPosX, newPosY;
    int attackPower;

    int speed;
    int moral;
    int defensePower;
    bool movable;
    int collisionState;
    double width,height; // SEE
    double angle;


private:


};

#endif // UNIT_H
