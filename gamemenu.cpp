#include "gamemenu.h"
#include "ui_gamemenu.h"

GameMenu::GameMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameMenu)
{
    ui->setupUi(this);
    ui->sc1->setVisible(false);
    ui->sc2->setVisible(false);
    ui->sc3->setVisible(false);
    ui->sc4->setVisible(false);

    connect(ui->playButton,&QPushButton::clicked,this,&GameMenu::playButtonClicked);//connect(sender(ui),signal to capture/catch,receiver(this class),slot(func to run));
    connect(ui->exitButton,&QPushButton::clicked,this,&GameMenu::exitGame);//to invoke the exitGame function when the exit button clicked.
}

GameMenu::~GameMenu()
{
    delete ui;
    delete game;
    delete scenario;
}

void GameMenu::playGame(){
    game=new Game(*scenario);
    setCentralWidget(game);//changes the main scene
}
void GameMenu::exitGame(){
    QCoreApplication::quit();//to quit the app
}

void GameMenu::playButtonClicked()
{
    ui->playButton->setEnabled(false);
    ui->exitButton->setEnabled(false);
    ui->playButton->setVisible(false);
    ui->exitButton->setVisible(false);
    ui->sc1->setVisible(true);
    ui->sc2->setVisible(true);
    ui->sc1->setEnabled(true);
    ui->sc2->setEnabled(true);
    ui->sc3->setVisible(true);
    ui->sc4->setVisible(true);
    ui->sc3->setEnabled(true);
    ui->sc4->setEnabled(true);

}



void GameMenu::on_sc1_clicked()
{
    scenario=new Scenario(1);
    playGame();
}


void GameMenu::on_sc2_clicked()
{
    scenario=new Scenario(2);
    playGame();
}

void GameMenu::on_sc3_clicked()
{
    scenario=new Scenario(3);
    playGame();
}


void GameMenu::on_sc4_clicked()
{
    scenario=new Scenario(4);
    playGame();
}

