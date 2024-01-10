#ifndef SCENARIO_H
#define SCENARIO_H
#include <QImage>
#include<QFile>
#include<QDir>
using namespace std;
/**
 * @brief The Scenario class represents a scenario with units, obstacles, and a map.
 *
 * The Scenario class provides methods to retrieve information about unit positions,
 * unit types, map image, obstacle positions, obstacle types, and unit color for a
 * given scenario.
 */
class Scenario
{
public:
    /**
     * @brief Constructs a Scenario object with the specified scenario number and scale.
     * @param scenarioNum The scenario number.
     * @param scale The scale factor applied to the scenario.
     */
    Scenario(int scenarioNum,double scale);
    /**
     * @brief Gets the positions of units for a specific player.
     * @param index The player index (0 or 1).
     * @return A QVector containing the positions of units.
     */
    QVector<QPointF> getUnitPositions(int index);
    /**
     * @brief Gets the types of units for a specific player.
     * @param index The player index (0 or 1).
     * @return A QList containing the types of units.
     */
    QList<QString>getUnitsType(int index);
    /**
     * @brief Gets the image of the map for the scenario.
     * @return A QImage representing the map image.
     */
    QImage  getMapImage();
    /**
     * @brief Gets the positions of obstacles on the map.
     * @return A QVector containing QVector of QPointF representing obstacle positions.
     */
    QVector<QVector<QPointF>> getObstaclePositions();
    /**
     * @brief Gets the types of obstacles on the map.
     * @return A QList containing the types of obstacles.
     */
    QList<QString> getObstacleTypes();
    /**
     * @brief Gets the color associated with units in the scenario.
     * @return A QColor representing the unit color.
     */
    QColor getUnitColor();
private:
    /**
     * @brief Reads and processes the scenario file at the specified path.
     * @param path The path to the scenario file.
     * @param scale The scale factor applied to the scenario.
     */
    void scanScenarioFile(QString path,double scale);
    QString mapImagePath; ///< Path to the map image file.
    QString scenarioPath; ///< Path to the scenario file.
    QVector<QPointF> unitPositions[2]; ///< Positions of units for each player.
    QList<QString> unitTypes[2]; ///< Types of units for each player.
    QVector<QVector<QPointF>> obstaclesPositions; ///< Positions of obstacles on the map.
    QList<QString> obstacleTypes; ///< Types of obstacles on the map.
    QColor unitColor; ///< Color associated with units in the scenario.
};

#endif // SCENARIO_H

