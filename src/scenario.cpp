#include "Scenario.h"


Scenario::Scenario(int scenarioNum,double scale){
    scenarioPath.append(":/scenarios/scenarios/scenario").append(to_string(scenarioNum)).append(".txt");
    mapImagePath.append(":/images/images/map").append(to_string(scenarioNum)).append(".png");
    scanScenarioFile(scenarioPath,scale);
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



QVector<QVector<QPointF>> Scenario::getObstaclePositions()
{
    return obstaclesPositions;
}



QVector<QString> Scenario::getObstacleTypes()
{
    return obstacleTypes;
}


void Scenario::scanScenarioFile(QString fileName, double scale) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error opening file:" << file.errorString();
        return;
    }
    else{
        QTextStream in(&file);
        QString declaration;
            QPointF pos;
        try {
            while (!in.atEnd()) {
                QStringList decLineContent = in.readLine().split(" ");
                if (decLineContent.isEmpty()) {
                    qDebug() << "Error: Empty line encountered.";
                    continue;
                }
                declaration = decLineContent[0];
                if (declaration == "Unit:") {
                    QString userType = decLineContent[1], unitType = decLineContent[2];
                        QStringList positionsLine = in.readLine().split(" ");
                        if(positionsLine.isEmpty()){qDebug("Unit positions are not specified.");}
                        for (int i = 0; i < positionsLine.size(); i++) {
                            pos = {positionsLine[i].split(",")[0].toDouble()*scale,positionsLine[i].split(",")[1].toDouble()*scale};
                            userType == "User:" ? (unitPositions[0].push_back(pos), unitTypes[0].push_back(unitType)) : (unitPositions[1].push_back(pos), unitTypes[1].push_back(unitType));
                        }

                }
                else if (declaration == "map:") {
                    QString obstacleType = decLineContent[1];
                    QStringList positionsLine = in.readLine().split(" ");
                    if(positionsLine.isEmpty()){qDebug("Obstacles positions are not specified.");}
                    obstacleTypes.push_back(obstacleType);
                    QVector<QPointF> obstaclePositions;
                    for (QString positions:positionsLine) {
                            pos={positions.split(",")[0].toDouble()*scale,positions.split(",")[1].toDouble()*scale};
                        obstaclePositions.push_back(pos);
                    }
                    if(obstacleType=="swamp"){obstaclePositions.push_back(obstaclePositions[0]);}
                    obstaclesPositions.push_back(obstaclePositions);
                }

            }

        file.close();
        }catch (const std::exception &e) {
            qDebug() << "Error while processing file:" << e.what();
        }
    }
}
