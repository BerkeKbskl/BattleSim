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
    list<string>getUserUnitsType();
    vector<QPointF>  getAIUntisPositions();
    list<string>getAIUnitsType();
    QImage  getMapImage();
private:
    bool scanScenarioFile(QString path);
    QString mapImagePath;
    QString scenarioPath;
    vector<QPointF> userUnitsPositions;
    list<string>userUnitsTypes;
    vector<QPointF> AIUnitsPositions;
    list<string>AIUnitsTypes;
};

#endif // SCENARIO_H
