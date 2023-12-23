#ifndef GAME_H
#define GAME_H

#include<QWidget>
#include<QTimer>
#include<QPainter>
#include<QMouseEvent>
#include "ai.h"
#include "map.h"
#include"user.h"
#include"scenario.h"


class Game : public QWidget
{
public:
    Game(Scenario scenario,QWidget *parent = nullptr);
    ~Game();
    QTimer* timer;

    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent* event)override;
    void updateGame();

private:
    void checkState();
    Scenario scenario;
    void gameSetup();
    Map map;
    User user;
    AI ai;
};

#endif // GAME_H
