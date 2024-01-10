#include <QMainWindow>
#include "game.h"
#include"scenario.h"
#include "settings.h"
#include<QLabel>
#include <QMediaPlayer>
#include <QAudioOutput>

QT_BEGIN_NAMESPACE
namespace Ui { class GameMenu; }
QT_END_NAMESPACE
/**
 * @brief The GameMenu class represents the main menu of the game application.
 *
 * The GameMenu class inherits from QMainWindow and provides functionality for
 * starting the game, navigating through the menu, adjusting settings, and displaying
 * information on how to play the game.
 */
class GameMenu : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a GameMenu object.
     * @param parent The parent widget (default is nullptr).
     */
    GameMenu(QWidget *parent = nullptr);
    /**
     * @brief Destroys the GameMenu object.
     */

    ~GameMenu();
private slots:
    /**
     * @brief Slot function to handle the exit game action.
     */
    void exitGame();
    /**
     * @brief Slot function to handle the play button click.
     */
    void playButtonClicked();
    /**
     * @brief Slot function to show the main menu.
     */
    void showMenu();
    /**
     * @brief Slot function to show the how-to-play information.
     */
    void showHowToPlay();
    /**
     * @brief Slot function to apply the selected scenario.
     */
    void applyScenario();
    /**
     * @brief Slot function to navigate back in the menu.
     */
    void back();
    /**
     * @brief Slot function to change the how-to-play image.
     * @param index The index of the image to be displayed.
     */
    void changeHtpImage(int);
    /**
     * @brief Slot function to show the game settings.
     */
    void showSettings();
    /**
     * @brief Slot function to apply adjustments made in the settings.
     */
    void applyAdjustments();
private:
    void showSelectedScenarioImgae();
    void gameMenuSetup();
    void playGame();
    QSize oldSize;
    Scenario *scenario;
    Settings settings;
    Ui::GameMenu *ui;
    Game *game;
    QMediaPlayer *player;///< Player object for the soundtrack.
    QAudioOutput *audioOutput;///< AudioOutput object for the soundtrack.

    /**
     * @brief Sets up the sound for the game menu.
     */
    void setSound();
};
