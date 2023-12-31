#ifndef SCENARIO_H
#define SCENARIO_H
#include <QImage>
#include<QFile>
#include<QDir>
using namespace std;
class Scenario
{
public:
    Scenario(int);
    QVector<QPointF> getUnitPositions(int index);
    QList<QString>getUnitsType(int index);
    QImage  getMapImage();
    QVector<QVector<QPointF>> getObstaclePositions();
    QList<QString> getObstacleTypes();
private:
    void scanScenarioFile(QString path);
    QString mapImagePath;
    QString scenarioPath;
    QVector<QPointF> unitPositions[2];
    QList<QString> unitTypes[2];
    QVector<QVector<QPointF>> obstaclesPositions;
    QList<QString> obstacleTypes;

};

#endif // SCENARIO_H
