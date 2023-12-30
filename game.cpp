#include "game.h"
#include "gamemenu.h"
#include "ui_game.h"
#define FPS 60

Game::Game(Scenario scenario,QWidget *parent)
    :QWidget(parent), scenario(scenario), map(scenario), user(scenario), ai(scenario),ui(new Ui::Game)
{   
    ui->setupUi(this);
    ui->pauseMenu->setVisible(false);
    setFocusPolicy(Qt::StrongFocus);
    // start updating frames.
    gameSetup();
}

Game::~Game(){
    delete timer;
    delete ui;
}

void Game::gameSetup(){

    ai.deployUnits(scenario);
    user.deployUnits(scenario);
    timer=new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Game::updateGame);
    connect(ui->pushButton_2,&QPushButton::clicked, this,&Game::exitToMenu);
    timer->start(1000/FPS);

}


void Game::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
    QPainter painter(this);
    map.draw(&painter);


    for(Unit *unit:user.units){
        if(unit!=0){
            QPainter painter(this);
            unit->draw(&painter);
        }
    }

    for(Unit *unit:ai.units){
        if(unit!=0){
            QPainter painter(this);
            unit->draw(&painter);
        }
    }

}

void Game::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        for (Unit *unit : user.units) {
            unit->selectUnit(event->pos());
        }
    }

    if (event->button() == Qt::RightButton
             && map.contains(event->pos())) {
        for (Unit *unit : user.units) {
                unit->setTarget(event->pos());
        }
    }
}

void Game::closePauseMenu()
{
    timer->start(1000 / 60);
    ui->pauseMenu->setVisible(false);

}

void Game::keyPressEvent(QKeyEvent* event)
{
    
        if (event->key() == Qt::Key_Escape) {
            ui->pauseMenu->setVisible(!ui->pauseMenu->isVisible()); 
            if (!ui->pauseMenu->isVisible()) 
                timer->start(1000 / 60);
            else
                timer->stop();
        }
        connect(ui->pushButton, &QPushButton::clicked, this, &Game::closePauseMenu);
        
}


void Game::manageCollisions() {

    auto coll = [&](const auto& units1, const auto& units2) {

        for (Unit* unit : units1) {
            QPainterPath nextPath = unit->getNextPath();

            // For direct collisions.
            for (Unit* trUnit : units1) {
                if (trUnit != unit && nextPath.intersects(trUnit->getCurrentPath())) {
                    unit->stop();
                }
            }

            for (Obstacle* o : map.obstacles) {
                if (unit->getNextPath().intersects(o->shape)) {
                    unit->stop();
                }
            }

            for (Unit* trUnit : units2) {
                if (nextPath.intersects(trUnit->getCurrentPath())) {
                    unit->stop();
                }

                // Receive attacks (may do opposite)
                if (nextPath.intersects(trUnit->getAttackCollider())) {
                    trUnit->attack(*unit);
                }
            }


        }


    };

    if (user.units.empty() || ai.units.empty()) {
        timer->stop();
        emit showResult();
    } else {
        coll(user.units, ai.units);
        coll(ai.units, user.units);
    }
}


void Game::updateGame(){

    manageCollisions();
    checkHealth();

    ai.makeMove(user.units);

    for (Unit *unit : user.units) {
        unit->moveTo();
    }

    for (Unit *unit : ai.units) {
        unit->moveTo();
    }



    update(); // calls paintEvent
}

void Game::checkHealth() {

    auto removeDeadUnits = [&](auto& units) {
        units.erase(std::remove_if(units.begin(), units.end(),
                                   [](Unit* unit) { return unit->getHealth() <= 0; }),
                    units.end());
    };

    removeDeadUnits(user.units);
    removeDeadUnits(ai.units);
}
