#include "ResultWidget.h"
#include "ui_ResultWidget.h"
#include "GameMenu.h"

ResultWidget::ResultWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::ResultWidget)
{
    ui->setupUi(this);
    ui->exitToMenuButton->setAutoFillBackground(true);

    connect(ui->exitToMenuButton, &QPushButton::clicked, this, &ResultWidget::exitToMenu);
    connect(ui->playAgainButton, &QPushButton::clicked, this, &ResultWidget::playAgain);

}

ResultWidget::~ResultWidget()
{
    delete ui;
}
