
#include <QMainWindow>
#include "game.h"
#include"scenario.h"
#include "resultwidget.h"

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
    void resultScreen();
    void showMenu();
    void on_sc1_clicked();
    void on_sc2_clicked();
    void on_sc3_clicked();
    void on_sc4_clicked();

private:
    void gameMenuSetup();
    void playGame();
    Scenario *scenario;
    Ui::GameMenu *ui;
    Game *game;
    ResultWidget *resultWidget=0;
};

