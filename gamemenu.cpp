#include "gamemenu.h"
#include "ui_gamemenu.h"

GameMenu::GameMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameMenu){
    gameMenuSetup();
}

GameMenu::~GameMenu(){
    delete ui;
    delete game;
    delete scenario;
}

/**
 * @brief Sets up the initial configuration of the game menu.
 *
 * This function sets up the UI elements, connects signals and slots, and prepares
 * the initial state of the game menu.
 */
void GameMenu::gameMenuSetup(){
    ui->setupUi(this);
    ui->gameMenuW->setCurrentIndex(0);
    connect(ui->playButton,&QPushButton::clicked,this,&GameMenu::playButtonClicked);//connect(sender(ui),signal to capture/catch,receiver(this class),slot(func to run));
    connect(ui->exitButton,&QPushButton::clicked,this,&GameMenu::exitGame);//to invoke the exitGame function when the exit button clicked.
    connect(ui->howTP_Button,&QPushButton::clicked,this,&GameMenu::showHowToPlay);
    connect(ui->comboBox,&QComboBox::currentIndexChanged,this,&GameMenu::showSelectedScenarioImgae);
    connect(ui->backToMenu,&QPushButton::clicked,this,&GameMenu::on_back_clicked);

}

/**
 * @brief Starts the game with the selected scenario.
 *
 * This function creates a new Game object with the selected scenario and connects signals
 * to handle events such as exiting to the menu or playing again.
 */
void GameMenu::playGame() {
    game = new Game(*scenario);
    connect(game,&Game::exitToMenu,this,&GameMenu::showMenu);
    connect(game,&Game::playAgain,this,&GameMenu::playGame);
    setCentralWidget(game);//changes the main scene
}

/**
 * @brief Exits the game.
 *
 * This function quits the application when called.
 */
void GameMenu::exitGame(){
    QCoreApplication::quit();//to quit the app
}

/**
 * @brief Shows the main menu.
 *
 * This function closes the game and resets the game menu setup to show the main menu.
 */
void GameMenu::showMenu() {
    game->close();
    game=nullptr;
    gameMenuSetup();//reset menu setup

}

/**
 * @brief Handles the play button click event.
 *
 * This function sets the current index of the game menu to show the appropriate UI page
 * and calls the function to display the selected scenario image.
 */
void GameMenu::playButtonClicked()
{
    ui->gameMenuW->setCurrentIndex(1);
    showSelectedScenarioImgae();
}

/**
 * @brief Shows the image corresponding to the selected scenario.
 *
 * This function constructs the file path for the selected scenario image and sets it
 * as the pixmap for the scenario image UI element.
 */
void GameMenu::showSelectedScenarioImgae(){
    QString imagePath=":/images/images/sc";
    imagePath.append(QString::number(ui->comboBox->currentIndex())).append(".jpg");
    ui->scenarioImage->setPixmap(QPixmap(imagePath));
}

/**
 * @brief Shows the "How to Play" section.
 *
 * This function sets the current index of the game menu to show the "How to Play" page
 * and connects the next and previous buttons to lambda expressions for image navigation.
 */
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

/**
 * @brief Applies the selected scenario and starts the game.
 *
 * This function creates a new Scenario object based on the selected index from the combo box
 * and initiates the game by calling the playGame function.
 */
void GameMenu::on_applyScenario_clicked()
{
    if (ui->comboBox->currentIndex() != 0) {
    scenario = new Scenario(ui->comboBox->currentIndex());
    playGame();
    }
}

/**
 * @brief Handles the back button click event.
 *
 * This function sets the current index of the game menu to go back to the main menu.
 */
void GameMenu::on_back_clicked()
{
    ui->gameMenuW->setCurrentIndex(0);
}

/**
 * @brief Changes the image displayed in the "How to Play" section.
 *
 * This function constructs the file path for the "How to Play" image based on the provided
 * image number and sets it as the pixmap for the "How to Play" panel UI element.
 *
 * @param num The image number to display.
 */
void GameMenu::changeHtpImage(int num)
{
    QString imagePath=":/images/images/htp";
    imagePath.append(QString::number(num)).append(".png");
    ui->htp_panel->setPixmap(QPixmap(imagePath));
}
