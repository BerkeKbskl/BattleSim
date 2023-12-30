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
}
void GameMenu::gameMenuSetup(){
    ui->setupUi(this);
    ui->gameMenuW->setCurrentIndex(0);
    connect(ui->playButton,&QPushButton::clicked,this,&GameMenu::playButtonClicked);//connect(sender(ui),signal to capture/catch,receiver(this class),slot(func to run));
    connect(ui->exitButton,&QPushButton::clicked,this,&GameMenu::exitGame);//to invoke the exitGame function when the exit button clicked.
    connect(ui->howTP_Button,&QPushButton::clicked,this,&GameMenu::showHowToPlay);
    connect(ui->comboBox,&QComboBox::currentIndexChanged,this,&GameMenu::showSelectedScenarioImgae);
    connect(ui->backToMenu,&QPushButton::clicked,this,&GameMenu::on_back_clicked);

}
void GameMenu::playGame() {
    game = new Game(*scenario);
    connect(game,&Game::exitToMenu,this,&GameMenu::showMenu);
    connect(game,&Game::playAgain,this,&GameMenu::playGame);
    setCentralWidget(game);//changes the main scene
}
void GameMenu::exitGame(){
    QCoreApplication::quit();//to quit the app
}
void GameMenu::showMenu() {
    game->close();
    game=nullptr;
    gameMenuSetup();//reset menu setup

}
void GameMenu::playButtonClicked()
{
    ui->gameMenuW->setCurrentIndex(1);
    showSelectedScenarioImgae();
}
void GameMenu::showSelectedScenarioImgae(){
    QString imagePath=":/images/images/sc";
    imagePath.append(QString::number(ui->comboBox->currentIndex())).append(".jpg");
    ui->scenarioImage->setPixmap(QPixmap(imagePath));
}
void GameMenu::showHowToPlay()
{
    static int imageNum;
    imageNum=1;
    ui->gameMenuW->setCurrentIndex(2);
    changeHtpImage(imageNum);

    // Disconnect existing connections
    disconnect(ui->next, &QPushButton::clicked, nullptr, nullptr);
    disconnect(ui->pre, &QPushButton::clicked, nullptr, nullptr);

    // Connect the buttons to the lambda expressions
    connect(ui->next, &QPushButton::clicked, this, [=]() {
        if (imageNum < 4)
            imageNum += 1;
        changeHtpImage(imageNum);
    });

    connect(ui->pre, &QPushButton::clicked, this, [=]() {
        if (imageNum > 1)
            imageNum -= 1;
        changeHtpImage(imageNum);
    });
}
void GameMenu::on_applyScenario_clicked()
{
    if (ui->comboBox->currentIndex() != 0) {
    scenario = new Scenario(ui->comboBox->currentIndex());
    playGame();
    }
}
void GameMenu::on_back_clicked()
{
    ui->gameMenuW->setCurrentIndex(0);
}
void GameMenu::changeHtpImage(int num)
{
    QString imagePath=":/images/images/htp";
    imagePath.append(QString::number(num)).append(".png");
    qDebug("%s",imagePath.toStdString().c_str());
    ui->htp_panel->setPixmap(QPixmap(imagePath));
}
