#include "game.h"
#include "gamemenu.h"
#include "ui_game.h"
#define FPS 60

Game::Game(Scenario scenario,QWidget *parent)
    :QWidget(parent), scenario(scenario), map(scenario), user(scenario), ai(scenario),ui(new Ui::Game)
{
    ui->setupUi(this);
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
    ui->gameW->setCurrentIndex(0);
    timer=new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Game::updateGame);
    connect(ui->exitToGMenu,&QPushButton::clicked, this,&Game::exitToMenu);
    connect(ui->playAgainButton,&QPushButton::clicked,this,&Game::playAgain);
    connect(ui->exitToMenuButton,&QPushButton::clicked,this,&Game::exitToMenu);
    connect(ui->pauseConButton, &QPushButton::clicked, this, &Game::pauseGame);
    timer->start(1000/FPS); // 60 FPS

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
void Game::showResult(){
    ui->gameW->setCurrentIndex(1);

}
void Game::pauseGame(){
    static int pauseState = 1;
    pauseState=pauseState==0?1:0;
    pauseState == 0 ? timer->stop(): timer->start(1000 / FPS;
    pauseState == 0 ? isPauseState=false:isPauseState=true;
}

void Game::mousePressEvent(QMouseEvent *event)
{
    if (isPauseState&&event->button() == Qt::LeftButton) { //selection ***left mouse button
        for (Unit *unit : user.units) {
            unit->selectUnit(event->pos());
        }
    }

    else if (isPauseState&&event->button() == Qt::RightButton
             && map.contains(event->pos())) { //moving ***right muse button
        //***
        for (Unit *unit : user.units) {
                unit->setTarget(event->pos());
        }
    }
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
        QPalette palette = ui->resText->palette();
        palette.setColor(QPalette::WindowText, Qt::white);
        ui->resText->setPalette(palette);
        ui->resText->setText(ai.units.empty()?("YOU WON"):("YOU ARE DEFEATED"));
        timer->stop();
        emit showResult();
    } else {
        coll(user.units, ai.units);
        coll(ai.units, user.units);
    }
}


void Game::updateGameInfo(){
    QString info="";
    info.append(" Remaining user units: ").append(QString::number(user.units.size())).append("\n");
    info.append(" Remaining enemy units: ").append(QString::number(ai.units.size())).append("\n");
    ui->label->setText(info);
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


    updateGameInfo();
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
