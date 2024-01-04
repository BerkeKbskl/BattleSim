#include <QMainWindow>
#include "game.h"
#include"scenario.h"
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
    void on_applyScenario_clicked();
    void on_back_clicked();
    void changeHtpImage(int);
private:
    void showSelectedScenarioImgae();
    void gameMenuSetup();
    void playGame();
    Scenario *scenario;
    Ui::GameMenu *ui;
    Game *game;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;

};

