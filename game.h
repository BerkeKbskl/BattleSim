#ifndef GAME_H
#define GAME_H

#include<QWidget>
#include<QTimer>
#include<QPainter>
#include<QMouseEvent>
#include<QKeyEvent>
#include "ai.h"
#include "map.h"
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
    Game(Scenario scenario, QWidget *parent = nullptr);
    ~Game();
    QTimer* timer;

    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent* event)override;
    void updateGame();
    void checkHealth();


signals:
    void playAgain();
    void exitToMenu();
private:
    void updateGameInfo();
    void pauseGame();
    void showResult();
    bool isPauseState;
    Ui::Game *ui;
    void manageCollisions();
    void gameSetup();
    Scenario scenario;
    Map map;
    User user;
    AI ai;
};

#endif // GAME_H
