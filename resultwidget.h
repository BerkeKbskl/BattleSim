#ifndef RESULTWIDGET_H
#define RESULTWIDGET_H

#include <QWidget>
#include <QPointer>
#include <QObject>

namespace Ui {
class ResultWidget;
}

class ResultWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ResultWidget(QWidget *parent = nullptr);
    ~ResultWidget();



signals:
    void exitToMenu();
    void playAgain();
private:
    Ui::ResultWidget *ui;
};

#endif // RESULTWIDGET_H
