#include "Scenario.h"
#include <iostream>

/**
 * @brief Construct a new Scenario object based on the specified scenario number.
 *
 * Initializes a Scenario object with paths to scenario and map image files and scans
 * the scenario file to extract information about unit and obstacle positions.
 *
 * @param scenarioNum The scenario number.
 */
Scenario::Scenario(int scenarioNum) {
    scenarioPath.append(":/scenarios/scenarios/scenario").append(to_string(scenarioNum)).append(".txt");
    mapImagePath.append(":/images/images/map").append(to_string(scenarioNum)).append(".png");
        scanScenarioFile(scenarioPath);
}

/**
 * @brief Get the positions of units based on the specified index.
 *
 * @param index The index indicating which set of unit positions to retrieve (999 for User).
 * @return The QVector of QPointF representing the unit positions.
 */
QVector<QPointF> Scenario::getUnitPositions(int index) {
    return index == 999 ? unitPositions[0] : unitPositions[1];
}

/**
 * @brief Get the types of units based on the specified index.
 *
 * @param index The index indicating which set of unit types to retrieve.
 * @return The QList of QString representing the unit types.
 */
QList<QString> Scenario::getUnitsType(int index) {
    return index == 999 ? unitTypes[0] : unitTypes[1];
}

/**
 * @brief Get the map image associated with the scenario.
 *
 * @return The QImage representing the map image.
 */
QImage Scenario::getMapImage() {
    return  QImage(mapImagePath);
}

/**
 * @brief Get the positions of obstacles in the scenario.
 *
 * @return The QList of QPointF representing the obstacle positions.
 */
QVector<QVector<QPointF>> Scenario::getObstaclePositions()
{
    return obstaclesPositions;
}

/**
 * @brief Get the types of obstacles in the scenario.
 *
 * @return The QVector of QString representing the obstacle types.
 */
QVector<QString> Scenario::getObstacleTypes()
{
    return obstacleTypes;
}

/**
 * @brief Scan the scenario file and extract information about units and obstacles.
 *
 * Reads the scenario file line by line, extracts information about unit and obstacle
 * positions and types, and populates the corresponding data structures.
 *
 * @param fileName The path to the scenario file.
 */
void Scenario::scanScenarioFile(QString fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error opening file:" << file.errorString();
        return;
    }
    else{
        QTextStream in(&file);
        QString declaration;
        double xPos, yPos;
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
                            xPos = positionsLine[i].split(",")[0].toDouble();
                            yPos = positionsLine[i].split(",")[1].toDouble();
                            userType == "User:" ? (unitPositions[0].push_back({ xPos, yPos }), unitTypes[0].push_back(unitType)) : (unitPositions[1].push_back({ xPos, yPos }), unitTypes[1].push_back(unitType));
                        }

                }
                else if (declaration == "map:") {
                    QString obstacleType = decLineContent[1];
                    QStringList positionsLine = in.readLine().split(" ");
                    if(positionsLine.isEmpty()){qDebug("Obstacles positions are not specified.");}
                    obstacleTypes.push_back(obstacleType);
                    QVector<QPointF> obstaclePositions;
                    for (QString positions:positionsLine) {
                        obstaclePositions.push_back({ positions.split(",")[0].toDouble(),positions.split(",")[1].toDouble()});
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
