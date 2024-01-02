#include "game.h"
#include "gamemenu.h"
#include "ui_game.h"
#define FPS 60

/**
 * @brief Construct a new Game object with the specified scenario and parent.
 *
 * Initializes a Game object with the specified scenario, sets up the game, and starts updating frames.
 *
 * @param scenario The scenario containing information about the game setup.
 * @param parent The parent widget.
 */
Game::Game(Scenario scenario,QWidget *parent)
    :QWidget(parent), scenario(scenario), map(scenario), user(scenario), ai(scenario),ui(new Ui::Game),isGameStarted(false)
{
    ui->setupUi(this);
    setFocusPolicy(Qt::StrongFocus);
    // Start updating frames.
    gameSetup();
}

Game::~Game(){
    delete timer;
    delete ui;
}

/**
 * @brief Set up the initial state of the game.
 *
 * Initializes various game settings, deploys units for the user and AI, and connects signals to slots.
 */
void Game::gameSetup(){
    isPauseState = false;
    ai.deployUnits(scenario);
    user.deployUnits(scenario);
    ui->pauseIcon->hide();
    ui->gameW->setCurrentIndex(0);
    timer=new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Game::updateGame);
    connect(ui->exitToGMenu,&QPushButton::clicked, this,&Game::exitToMenu);
    connect(ui->playAgainButton,&QPushButton::clicked,this,&Game::playAgain);
    connect(ui->exitToMenuButton,&QPushButton::clicked,this,&Game::exitToMenu);
    connect(ui->pauseConButton, &QPushButton::clicked, this, &Game::pauseGame);
    connect(ui->startGameButton, &QPushButton::clicked, this, &Game::startGame);
    timer->start(1000/FPS);

}

/**
 * @brief Handle the paint event, drawing the map and units on the QPainter.
 *
 * This function is called whenever the widget needs to be redrawn, and it draws the map, user units, and AI units.
 *
 * @param event The paint event.
 */
void Game::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
    QPainter painter(this);
    map.draw(&painter);


    for(Unit *unit:user.getUnits()){
        if(unit!=0){
            QPainter painter(this);
            unit->draw(&painter);
        }
    }

    for(Unit *unit:ai.getUnits()){
        if(unit!=0){
            QPainter painter(this);
            unit->draw(&painter);
        }
    }

}

/**
 * @brief Show the result page when the game is over.
 */
void Game::showResult(){
    ui->gameW->setCurrentIndex(1);

}

/**
 * @brief Pause or resume the game when the pause button is clicked.
 */
void Game::pauseGame(){
    isPauseState = !isPauseState;
    isPauseState ? timer->stop(): timer->start(1000 / FPS);
    isPauseState?ui->pauseIcon->show():ui->pauseIcon->hide();
}

/**
 * @brief Handle mouse press events, selecting units and setting targets.
 *
 * If the game is not paused, left-clicking selects units, and right-clicking sets targets.
 *
 * @param event The mouse press event.
 */
void Game::mousePressEvent(QMouseEvent *event)
{
        static bool isAnyUnitSelected=false;
        if (!isPauseState&&event->button() == Qt::LeftButton) {
            for (Unit *unit : user.getUnits()) {
            if(isGameStarted){unit->selectUnit(event->pos());}
            else if(!isAnyUnitSelected){isAnyUnitSelected=unit->selectUnit(event->pos());}
            }
        }

        else if (!isPauseState&&event->button() == Qt::RightButton
                 && map.contains(event->pos())) {
            for (Unit *unit : user.getUnits()) {
            isAnyUnitSelected=false;
            isGameStarted?unit->setTarget(event->pos()):unit->manualMove(event->pos(),QRectF(0,0,ui->manuelDeployBorder->width(),ui->manuelDeployBorder->height()),map.getObstacles(),user.getUnits());
            }
        }



}

/**
 * @brief Manages collisions between units and obstacles in the game.
 *
 * This function checks for collisions between units, obstacles, and attack colliders,
 * updating the game state accordingly. It handles both direct collisions between units
 * and collisions with obstacles on the map. Additionally, it allows units to receive attacks
 * from other units' attack colliders.
 */
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

            for (Obstacle* o : map.getObstacles()) {
                if (unit->getNextPath().intersects(o->getPath())) {
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

    if (user.getUnits().empty() || ai.getUnits().empty()) {
        QPalette palette = ui->resText->palette();
        palette.setColor(QPalette::WindowText, Qt::white);
        ui->resText->setPalette(palette);
        ui->resText->setText(ai.getUnits().empty()?("YOU WON"):("YOU ARE DEFEATED"));
        timer->stop();
        emit showResult();
    } else {
        coll(user.getUnits(), ai.getUnits());
        coll(ai.getUnits(), user.getUnits());
    }
}
/**
 * @brief Updates the game state.
 *
 * This function manages collisions, checks health of units, makes AI moves,
 * updates unit positions, updates game information, and triggers a repaint.
 */
void Game::updateGame(){
    if(isGameStarted){
    ai.makeMove(user.getUnits());
    manageCollisions();
    checkHealth();



    for (Unit *unit : user.getUnits()) {
        unit->moveTo();
    }

    for (Unit *unit : ai.getUnits()) {
        unit->moveTo();
    }
    }
    // Update info in the UI.
    QString info="";
    info.append(" Remaining user units: ").append(QString::number(user.getUnits().size())).append("\n");
    info.append(" Remaining enemy units: ").append(QString::number(ai.getUnits().size())).append("\n");
    ui->info->setText(info);
    update(); // calls paintEvent
}

/**
 * @brief Checks the health of units and removes dead units from the game.
 *
 * This function removes units with health equal to or below zero from both
 * the user and AI unit lists.
 */

void Game::checkHealth() {

    for (Unit* unit : user.getUnits()) {
        if (unit->getHealth() <= 0) {
            user.removeUnits(unit);
        }
    }

    for (Unit* unit : ai.getUnits()) {
        if (unit->getHealth() <= 0) {
            ai.removeUnits(unit);
        }
    }

}


void Game::startGame()
{
    ui->manuelDeployBorder->setVisible(false);
    ui->startGameButton->setVisible(false);
    isGameStarted=true;
}

