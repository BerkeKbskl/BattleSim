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
    vector<QPointF> getUnitPositions(int index);
    list<QString>getUnitsType(int index);
    QImage  getMapImage();
private:
    void scanScenarioFile(QString path);
    QString mapImagePath;
    QString scenarioPath;
    vector<QPointF> unitPositions[2];
    list<QString>unitTypes[2];
};

#endif // SCENARIO_H
