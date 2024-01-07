#ifndef GAME_H
#define GAME_H

#include<QWidget>
#include<QTimer>
#include<QPainter>
#include<QMouseEvent>
#include<QKeyEvent>
#include "ai.h"
#include "map.h"
#include "settings.h"
#include"user.h"
#include"scenario.h"
#include<QObject>

namespace Ui {
class Game;
}

class Game : public QWidget
{
    Q_OBJECT
public:
    Game(Scenario scenario,Settings settings, QWidget *parent = nullptr);
    ~Game();

signals:
    void playAgain();
    void exitToMenu();

private:
    Ui::Game *ui;
    Settings settings;
    QTimer* timer;
    Scenario scenario;
    Map map;
    User user;
    AI ai;
    void startGame();
    bool isGameStarted;
    void pauseGame();
    void showResult();
    bool isPauseState;
    void manageCollisions();
    void gameSetup();
    void checkHealth();
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent* event)override;
    void updateGame();
};

#endif // GAME_H
