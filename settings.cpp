#include "settings.h"

Settings::Settings(): scale(1.0), screenSize(QSize(1366, 768))
{

}

double Settings::getScale()
{
    return scale;
}

void Settings::setScale(double newScale)
{
    scale=newScale>0.99?newScale:1.0;
}

QSize Settings::getScreenSize()
{
    return screenSize;
}

void Settings::setScreenSize(QSize newSize)
{
    screenSize=newSize;
}

