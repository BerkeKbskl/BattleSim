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

class GameMenu : public QMainWindow
{
    Q_OBJECT

public:
    GameMenu(QWidget *parent = nullptr);
    ~GameMenu();
private slots:
    void exitGame();
    void playButtonClicked();
    void showMenu();
    void showHowToPlay();
    void applyScenario();
    void back();
    void changeHtpImage(int);
    void showSettings();
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
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    void setSound();
};

