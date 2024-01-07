#ifndef SETTINGS_H
#define SETTINGS_H
#include <QSize>

class Settings
{
public:
    Settings();
    double getScale();
    void setScale(double scale);
    QSize getScreenSize();
    void setScreenSize(QSize);
private:
    double scale;
    QSize screenSize;
};

#endif // SETTINGS_H
