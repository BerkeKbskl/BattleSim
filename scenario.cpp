#include "Scenario.h"
#include <iostream>


Scenario::Scenario(int scenarioNum) {
    scenarioPath.append(":/scenarios/scenarios/scenario").append(to_string(scenarioNum)).append(".txt");
    mapImagePath.append(":/images/images/map").append(to_string(scenarioNum)).append(".png");
    scanScenarioFile(scenarioPath);

}

QVector<QPointF> Scenario::getUnitPositions(int index) {
    return index == 999 ? unitPositions[0] : unitPositions[1];
}


QList<QString> Scenario::getUnitsType(int index) {
    return index == 999 ? unitTypes[0] : unitTypes[1];
}



QImage Scenario::getMapImage() {
    return  QImage(mapImagePath);
}

QList<QPointF> Scenario::getObstaclePositions()
{
    return obstaclePositions;
}

QVector<QString> Scenario::getObstacleTypes()
{
    return obstacleTypes;
}

void Scenario::scanScenarioFile(QString fileName) {
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString declaration;
        double xPos, yPos;

        while (!in.atEnd()) {
            QStringList decLineContent = in.readLine().split(" ");
            declaration = decLineContent[0];
            if (declaration == "Unit:") {
                QString userType = decLineContent[1], unitType = decLineContent[2];
                    QStringList positionsLine = in.readLine().split(" ");
                    for (int i = 0; i < positionsLine.size(); i++) {
                        xPos = positionsLine[i].split(",")[0].toDouble();
                        yPos = positionsLine[i].split(",")[1].toDouble();
                        userType == "User:" ? (unitPositions[0].push_back({ xPos, yPos }), unitTypes[0].push_back(unitType)) : (unitPositions[1].push_back({ xPos, yPos }), unitTypes[1].push_back(unitType));
                    }

            }
            else if (declaration == "map:") {
                QString obstacleType = decLineContent[1];
                QStringList positionsLine = in.readLine().split(" ");
                for (int i = 0; i < positionsLine.size(); i++) {
                    xPos = positionsLine[i].split(",")[0].toDouble();
                    yPos = positionsLine[i].split(",")[1].toDouble();
                    obstaclePositions.push_back({ xPos,yPos });
                    obstacleTypes.push_back(obstacleType);
                }

            }

        }

        file.close();
    }
}
