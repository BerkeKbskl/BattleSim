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
    void draw(QPainter *);
    void rotate(double degrees);
    QPolygonF getNextPoly();
    double getAngle();
    double getOrientation();
    vector<int> target;
    void setCollisionState(int index);
    void setTarget(QPoint point);
    bool selected;
    double orientation;
    QColor color;
    QPolygonF shape;
    QImage img;
    int attack(Unit* enemy);
protected:


    double newPosX, newPosY;
    int attackPower;
    int health;
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
