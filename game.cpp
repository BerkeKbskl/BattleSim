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


void Game::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) { //selection ***left mouse button
        for (Unit *unit : user.units) {
            unit->selectUnit(event->pos());
            // rotate unit.
        }
    }

    else if (event->button() == Qt::RightButton
             && map.contains(event->pos())) { //moving ***right muse button
        //***
        for (Unit *unit : user.units) {
            if (unit->selected) {
                unit->setTarget(event->pos());

                QTransform rotationTransform;
                rotationTransform.translate(unit->shape.boundingRect().center().x(),
                                            unit->shape.boundingRect().center().y());
                //std::cout << unit->getAngle() << endl;
                rotationTransform.rotate(-unit->orientation * 180 / (M_PI) + 90
                                         + unit->getAngle() * 180 / (M_PI) + 90);
                unit->orientation = unit->getAngle();
                rotationTransform.translate(-unit->shape.boundingRect().center().x(),
                                            -unit->shape.boundingRect().center().y());
                unit->shape = rotationTransform.map(unit->shape);
                cout << "Clicked pos: " << event->pos().x() << ","
                     << event->pos().y() << endl;
            }
        }
    }
}

void Game::checkState()
{
    if (user.units.empty() || ai.units.empty()) {
        timer->stop();
        emit showResult();

    }

    for (Unit *unit : user.units) {
        QPolygonF nextPolygon = unit->getNextPoly();
        unit->setCollisionState(0); // Reset collision state for the current unit

        bool collisionDetected = false;  // Flag to indicate if a collision was detected

        for (Unit *trUnit : user.units) {
            if (trUnit != unit && nextPolygon.intersected(trUnit->shape).isEmpty() == false) {
                unit->setCollisionState(0);

                trUnit->setCollisionState(0);
                //unit->color = Qt::black;
                //trUnit->color = Qt::black;
                collisionDetected = false;

            }
        }

        if (!collisionDetected) {
            for (Unit *trUnit : ai.units) {
                if (nextPolygon.intersected(trUnit->shape).isEmpty() == false) {
                    unit->setCollisionState(2);
                    trUnit->setCollisionState(2);

                    if(unit->attack(*trUnit)){
                        ai.units.erase(std::remove(ai.units.begin(),ai.units.end(),trUnit),ai.units.end());
                    }

                    else if(trUnit->attack(*unit)){
                        user.units.erase(std::remove(user.units.begin(),user.units.end(),unit),user.units.end());
                    }


                    collisionDetected = true;
                } else

                // If it is not beneath but somewhere close for artillery
                if (unit->getNextCollider().intersected(trUnit->shape).isEmpty() == false) {
                    if(unit->attack(*trUnit)){
                        ai.units.erase(std::remove(ai.units.begin(),ai.units.end(),trUnit),ai.units.end());
                    }
                    collisionDetected = true;
                }
            }
        }

        if (!collisionDetected) {
            for (Obstacle* o : map.obstacles) {

                if (unit->shape.intersects(o->shape.toFillPolygon())) {
                    unit->setCollisionState(3);
                    collisionDetected = true;
                }
            }
        }
    }

    




    for (Unit *unit : ai.units) {
        QPolygonF nextPolygon = unit->getNextPoly();
        unit->setCollisionState(0); // Reset collision state for the current unit

        bool collisionDetected = false;  // Flag to indicate if a collision was detected

        for (Unit *trUnit : ai.units) {
            if (trUnit != unit && nextPolygon.intersected(trUnit->shape).isEmpty() == false) {
                unit->setCollisionState(0);
                trUnit->setCollisionState(0);
                //unit->color = Qt::black;
                //trUnit->color = Qt::black;
                collisionDetected = false;
            }
        }

        if (!collisionDetected) {
            for (Unit *trUnit : user.units) {
                if (nextPolygon.intersected(trUnit->shape).isEmpty() == false) {
                    unit->setCollisionState(2);
                    trUnit->setCollisionState(2);

                    if(unit->attack(*trUnit)){
                        user.units.erase(std::remove(user.units.begin(),user.units.end(),trUnit),user.units.end());
                    }

                    else if(trUnit->attack(*unit)){
                        ai.units.erase(std::remove(ai.units.begin(),ai.units.end(),unit),ai.units.end());
                    }
                    collisionDetected = true;
                } else

                // If it is not beneath but somewhere close for artillery
                if (unit->getNextCollider().intersected(trUnit->shape).isEmpty() == false) {
                    if(unit->attack(*trUnit)){
                        user.units.erase(std::remove(user.units.begin(),user.units.end(),trUnit),user.units.end());
                    }
                    unit->attack(*trUnit);
                    collisionDetected = true;
                }
            }
        }

        if (!collisionDetected) {
            for (Obstacle* o : map.obstacles) {

                if (unit->shape.intersects(o->shape.toFillPolygon())) {
                    unit->setCollisionState(3);
                    collisionDetected = true;
                }

            }
        }
    }

}



void Game::updateGame(){

    ai.makeMove(user.units);

    checkState();

    for (Unit *unit : user.units) {
        unit->moveTo();
    }

    for (Unit *unit : ai.units) {
        unit->moveTo();
    }



    update(); // calls paintEvent
}
