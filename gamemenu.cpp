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
    ui->frame->setVisible(false);
    
    connect(ui->playButton,&QPushButton::clicked,this,&GameMenu::playButtonClicked);//connect(sender(ui),signal to capture/catch,receiver(this class),slot(func to run));
    connect(ui->exitButton,&QPushButton::clicked,this,&GameMenu::exitGame);//to invoke the exitGame function when the exit button clicked.
    connect(ui->comboBox,&QComboBox::currentIndexChanged,this,&GameMenu::showSelectedScenarioImgae);
}

void GameMenu::playGame() {
    if (scenario) {
    if (resultWidget != nullptr) {
        resultWidget->close();
        resultWidget = nullptr;
    }
    game = new Game(*scenario);
    game->resize(1500, 800);
    connect(game, &Game::showResult, this, &GameMenu::resultScreen);
    connect(game, &Game::exitToMenu, this, &GameMenu::showMenu);
    setCentralWidget(game);//changes the main scene
}
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
void GameMenu::showMenu() {
    if (resultWidget!=nullptr) {
    resultWidget->close();
    resultWidget = nullptr;
    }
    game->close();
    game=nullptr;
    gameMenuSetup();//reset menu setup

}
void GameMenu::playButtonClicked()
{
    ui->menuWidget->setVisible(false);
    ui->frame->setVisible(true);
    showSelectedScenarioImgae();
}
void GameMenu::showSelectedScenarioImgae(){
    QString imagePath=":/images/images/sc";
    imagePath.append(QString::number(ui->comboBox->currentIndex())).append(".jpg");
    ui->scenarioImage->setPixmap(QPixmap(imagePath));
}
void GameMenu::on_applyScenario_clicked()
{
    if (ui->comboBox->currentIndex() != 0) {
    scenario = new Scenario(ui->comboBox->currentIndex());
    playGame();
    }

}

