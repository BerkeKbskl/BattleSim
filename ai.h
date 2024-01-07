#ifndef AI_H
#define AI_H

#include "player.h"
class AI : public Player

{

public:

    AI(Scenario scenario);

    void deployUnits(Scenario scenario) override;
    void makeMove(QVector<Unit *> enemyUnits, QVector<Obstacle *> obstacles);
    double squareDistanceTo(const QPointF& p1, const QPointF& p2);
    void normalize(QPointF& v);
private:
    QPointF closestPointOnPath(const QPointF &point, const QPainterPath &path);
    QPointF getRepulsionForce(double x, double y, const QPainterPath& obstaclePath);
    QPointF getAttractionForce(double x, double y, const QPointF& enemyPosition);
    QPointF getFriendForce(double x, double y, const QPointF& friendPosition);
    QPointF computeVectorField(Unit* unit, const QVector<Obstacle*>& obstacles,const QVector<Unit*>& enemies,const QVector<Unit*>& friends);
};


#endif // AI_H
