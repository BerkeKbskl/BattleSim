#include "Scenario.h"
#include <iostream>




Scenario::Scenario(int scenarioNum) {
    scenarioPath.append("scenario").append(to_string(scenarioNum)).append(".txt");
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
                if (unitType == "infantry:" || unitType == "cavalry:"||unitType=="artillery:") {
                    QString line=in.readLine();
                    QStringList positionsLine = line.split(" ");
                    for (int i = 0; i < positionsLine.size(); i += 2) {
                        xPos=positionsLine[i].toDouble();
                        yPos=positionsLine[i+1].toDouble();
                        if (userType == "User:") {
                            userUnitsPositions.push_back({xPos, yPos});
                            if (unitType == "infantry:") {
                                userUnitsTypes.push_back("infantry");
                            } else if (unitType == "cavalry:") {
                                userUnitsTypes.push_back("cavalry");
                            }else if (unitType == "artillery:") {
                                userUnitsTypes.push_back("artillery");
                            }

                        } else if (userType == "AI:") {
                            AIUnitsPositions.push_back({xPos, yPos});
                            if (unitType == "infantry:") {
                                AIUnitsTypes.push_back("infantry");
                            }else if (unitType == "cavalry:") {
                                AIUnitsTypes.push_back("cavalry");
                            }else if (unitType == "artillery:") {
                                AIUnitsTypes.push_back("artillery");
                            }
                        }
                    }
                }else {
                    qDebug() << "undefined definition for unit " ;
                }

            }
            else{

            }

        }

        file.close();
        return true;
    } else {
        qDebug() << "Dosya açma hatası!";
        return false;
    }
}
