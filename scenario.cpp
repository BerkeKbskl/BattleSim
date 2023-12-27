#include "Scenario.h"
#include <iostream>


Scenario::Scenario(int scenarioNum) {
    scenarioPath.append(":/scenarios/scenarios/scenario").append(to_string(scenarioNum)).append(".txt");
   //mapImagePath.append(":/images/images/map").append(to_string(scenarioNum)).append(".png");
    scanScenarioFile(scenarioPath);

}

vector<QPointF> Scenario::getUserUntisPositions() {
    return userUnitsPositions;
}

vector<QPointF> Scenario::getAIUntisPositions() {
    return AIUnitsPositions;
}
list<QString> Scenario::getUserUnitsType() {
    return userUnitsTypes;
}

list<QString> Scenario::getAIUnitsType() {
    return AIUnitsTypes;
}

QImage Scenario::getMapImage() {
    QImage mapImage(mapImagePath);
    return mapImage;
}

bool Scenario::scanScenarioFile(QString fileName) {
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString userType;
        QString unitType;
        QString declaration;
        double xPos, yPos;

        // Her satırı oku
        while (!in.atEnd()) {
            QString decLine=in.readLine();
            QStringList decLineContent = decLine.split(" ");
            declaration=decLineContent[0];
            if(declaration=="Unit:"){
                userType=decLineContent[1];
                unitType=decLineContent[2];
                if (unitType == "infantry" || unitType == "cavalry"||unitType=="artillery") {
                    QString line=in.readLine();
                    QStringList positionsLine = line.split(" ");
                    for (int i = 0; i < positionsLine.size(); i += 2) {
                        xPos=positionsLine[i].toDouble();
                        yPos=positionsLine[i+1].toDouble();
                        if (userType == "User:") {
                            userUnitsPositions.push_back({xPos, yPos});
                            userUnitsTypes.push_back(unitType);

                        } else if (userType == "AI:") {
                            AIUnitsPositions.push_back({xPos, yPos});
                            AIUnitsTypes.push_back(unitType);

                        }
                    }
                }else {
                    qDebug() << "undefined definition for unit " ;
                }

            }
            else{}/*
            else if(declaration=="map:"){
            Obstacle positions and other necessary informations

            }*/

        }

        file.close();
        return true;
    } else {
        qDebug() << "Dosya açma hatası!";
        return false;
    }
}
