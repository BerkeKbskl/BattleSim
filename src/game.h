#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include "ai.h"
#include "map.h"
#include "settings.h"
#include "user.h"
#include "scenario.h"
#include <QObject>

namespace Ui {
class Game;
}

/**
 * @brief The Game class represents the main game window.
 *
 * This class inherits from QWidget and provides the game interface,
 * handling game logic, user input, and updating the game state.
 */
class Game : public QWidget
{
    Q_OBJECT

public:

    /**
     * @brief Constructor for the Game class.
     * @param scenario The game scenario to be played.
     * @param settings The settings for the game.
     * @param parent The parent QWidget.
     */
    Game(Scenario scenario, Settings settings, QWidget *parent = nullptr);

    /**
     * @brief Destructor for the Game class.
     */
    ~Game();

signals:

    /**
     * @brief Signal emitted when the user chooses to play the game again.
     */
    void playAgain();

    /**
     * @brief Signal emitted when the user chooses to exit to the main menu.
     */
    void exitToMenu();

private:

    Ui::Game *ui; ///< The user interface for the game.
    Settings settings; ///< The settings for the game.
    QTimer* timer; ///< Timer for updating the game state.
    Scenario scenario; ///< The game scenario to be played.
    Map map; ///< The game map.
    User user; ///< The user-controlled player.
    AI ai; ///< The AI-controlled player.
    bool isGameStarted; ///< Flag indicating whether the game has started.
    bool isPauseState; ///< Flag indicating whether the game is in a paused state.

    /**
     * @brief Constructor for the Game class.
     */
    void startGame();

    /**
     * @brief Pause the game.
     */
    void pauseGame();

    /**
     * @brief Show the result of the game.
     */
    void showResult();

    /**
     * @brief Manages collisions. Checks every units next collider and stops the unit if its next collider intersects with other entities.
     * @note If the unit is colliding with an enemy unit then the functions calls attack function with passing intersected unit.
     */
    void manageCollisions();

    /**
     * @brief Check the health of units and handle any resulting actions.
     */
    void checkHealth();

    /**
     * @brief Set up the initial state of the game.
     */
    void gameSetup();

    /**
     * @brief Paint event for rendering the game.
     * @param event The QPaintEvent to be processed.
     */
    void paintEvent(QPaintEvent *event) override;

    /**
     * @brief Mouse press event for handling user input.
     * @note  This method selects the units that mouse clicked on it.
     * @param event The QMouseEvent to be processed.
     */
    void mousePressEvent(QMouseEvent* event) override;

    /**
     * @brief Update the game state.
     */
    void updateGame();
};

#endif // GAME_H
