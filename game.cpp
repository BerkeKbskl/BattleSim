#include "game.h"
#include <iostream>
#include "gamemenu.h"

Game::Game(Scenario scenario,QWidget *parent)
    : QWidget(parent), scenario(scenario), map(scenario), user(scenario), ai(scenario){
    setFocusPolicy(Qt::StrongFocus);
    // start updating frames.
    gameSetup();
}

Game::~Game(){
    delete timer;
}

void Game::gameSetup(){

    ai.deployUnits(scenario);
    user.deployUnits(scenario);
    timer=new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Game::updateGame);
    timer->start(1000/60); // 60 FPS

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


void Game::mousePressEvent(QMouseEvent *event) {

    if(event->button()==Qt::LeftButton ){//selection ***left mouse button
        for(Unit *unit:user.units){
        if(unit!=0){
            unit->selectUnit(event->pos());
            // rotate unit.
        }


        }
    }

    else if(event->button()==Qt::RightButton && map.contains(event->pos())){//moving ***right muse button
        //***
        for(Unit *unit:user.units){
            if(unit->selected)
            {
                unit->setTarget(event->pos());

                QTransform rotationTransform;
                rotationTransform.translate(unit->shape.boundingRect().center().x(),
                                            unit->shape.boundingRect().center().y());
                //std::cout << unit->getAngle() << endl;
                rotationTransform.rotate(-unit->orientation*180/(M_PI)+90+unit->getAngle()*180/(M_PI)+90);
                unit->orientation = unit->getAngle();
                rotationTransform.translate(-unit->shape.boundingRect().center().x(),
                                            -unit->shape.boundingRect().center().y());
                unit->shape = rotationTransform.map(unit->shape);
                cout << "Clicked pos: " << event->pos().x() << "," << event->pos().y();
            }

        }



    }
}

void Game::checkState(){
    for(Unit *unit:user.units){
        QPolygonF nextPolygon=unit->getNextPoly();

        for (Unit* trUnit : user.units) {

            if (trUnit != unit && nextPolygon.intersected(trUnit->shape).isEmpty() == false) {
                unit->setCollisionState(1);
                unit->color=(Qt::black);
                trUnit->color=(Qt::black);
                //friend unit
                return;
            }
        }

        for (Unit* trUnit : ai.units) {

            if (trUnit != unit && nextPolygon.intersected(trUnit->shape).isEmpty() == false) {
                unit->setCollisionState(1);
                if(unit->attack(trUnit)){
                    ai.units.erase(std::remove(ai.units.begin(),ai.units.end(),trUnit),ai.units.end());
                }
                return;
            }
        }

        for (Obstacle* o : map.obstacles) {
            if (!nextPolygon.intersected(o->shape).isEmpty()) {
                unit->setCollisionState(1);
                //methods for obstacles
                return;
            }
        }

        unit->setCollisionState(0);
        unit->moveTo();
    }
    if (user.units.empty() || ai.units.empty()) {
         timer->stop();
         emit showResult();

    }
}

void Game::updateGame(){

    checkState();

    update(); // calls paintEvent
}

