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

    void stop();
    void selectUnit(const QPointF);
    void setPosition(const QPointF v);
    void setTarget(const QPointF point);
    void moveTo();
    QPointF getPosition() const;
    QPainterPath getNextPath() const;
    QPainterPath getCurrentPath() const;

    virtual int attack(Unit& enemy);
    void takeDamage(int);

    bool isHelpNeed(); // for AI
    bool needHelp;
    bool helpAssigned;

    void setColor(const QColor);
    virtual void draw(QPainter *);

    int getHealth();
protected:

    double angle;
    QColor color;
    QPointF target;
    QPointF center;

    QImage img;
    int attackPower;
    int health;
    int speed;
    int defensePower;
    bool selected;
    bool movable;
    double width,height;



private:


};

#endif // UNIT_H
