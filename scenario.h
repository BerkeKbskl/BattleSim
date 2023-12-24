#ifndef SCENARIO_H
#define SCENARIO_H
#include <QImage>
#include <vector>
#include<QFile>
#include<QDir>
using namespace std;
class Scenario
{
public:
    Scenario(int);
    vector<QPointF> getUserUntisPositions();
    list<QString>getUserUnitsType();
    vector<QPointF>  getAIUntisPositions();
    list<QString>getAIUnitsType();
    QImage  getMapImage();
private:
    bool scanScenarioFile(QString path);
    QString mapImagePath;
    QString scenarioPath;
    vector<QPointF> userUnitsPositions;
    list<QString>userUnitsTypes;
    vector<QPointF> AIUnitsPositions;
    list<QString>AIUnitsTypes;
};

#endif // SCENARIO_H
