
#include <QMainWindow>
#include "game.h"
#include"scenario.h"
#include "resultwidget.h"
#include<QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class GameMenu; }
QT_END_NAMESPACE

class GameMenu : public QMainWindow
{
    Q_OBJECT

public:
    GameMenu(QWidget *parent = nullptr);
    ~GameMenu();
public slots:
    void exitGame();
    void playButtonClicked();
    void resultScreen();
    void showMenu();
private:
    void showSelectedScenarioImgae();
    void gameMenuSetup();
    void playGame();
    Scenario *scenario;
    Ui::GameMenu *ui;
    Game *game;
    ResultWidget *resultWidget=0;

};

