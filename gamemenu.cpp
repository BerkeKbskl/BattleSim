#include "gamemenu.h"
#include "ui_gamemenu.h"

GameMenu::GameMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameMenu)
{
    gameMenuSetup();

}

GameMenu::~GameMenu()
{
    delete ui;
    delete game;
    delete scenario;
    delete resultWidget;
}
void GameMenu::gameMenuSetup(){
    ui->setupUi(this);
    ui->scWidget->setVisible(false);
    connect(ui->playButton,&QPushButton::clicked,this,&GameMenu::playButtonClicked);//connect(sender(ui),signal to capture/catch,receiver(this class),slot(func to run));
    connect(ui->exitButton,&QPushButton::clicked,this,&GameMenu::exitGame);//to invoke the exitGame function when the exit button clicked.
}

void GameMenu::playGame(){
    if(resultWidget){
        resultWidget->close();
        resultWidget=0;
    }
    game = new Game(*scenario);
    connect(game,&Game::showResult,this,&GameMenu::resultScreen);
    setCentralWidget(game);//changes the main scene
}
void GameMenu::exitGame(){
    QCoreApplication::quit();//to quit the app
}
void GameMenu::resultScreen(){
    resultWidget=new ResultWidget(this);
    resultWidget->setGeometry(this->width()/2-resultWidget->width()/2,this->height()/2-resultWidget->height()/2,resultWidget->width(),resultWidget->height());
    connect(resultWidget,&ResultWidget::exitToMenu,this,&GameMenu::showMenu);
    connect(resultWidget,&ResultWidget::playAgain,this,&GameMenu::playGame);
    resultWidget->show();
}
void GameMenu::showMenu(){
    resultWidget->close();
    resultWidget = nullptr;
    game->close();
    game=nullptr;
    gameMenuSetup();//reset menu setup

}
void GameMenu::playButtonClicked()
{
    ui->menuWidget->setVisible(false);
    ui->scWidget->setVisible(true);
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

