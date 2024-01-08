#include "settings.h"

Settings::Settings(): scale(1.0), screenSize(QSize(1366, 768))
{

}
/**
* @brief Gets the current scale factor.
* @return The scale factor.
*/
double Settings::getScale()
{
    return scale;
}
/**
* @brief Sets the scale factor.
* @param newScale The new scale factor. Must be greater than 0.99.
*/
void Settings::setScale(double newScale)
{
    scale=newScale>0.99?newScale:1.0;
}
/**
* @brief Gets the current screen size.
* @return The current screen size.
*/
QSize Settings::getScreenSize()
{
    return screenSize;
}
/**
* @brief Sets the screen size.
* @param newSize The new screen size.
*/
void Settings::setScreenSize(QSize newSize)
{
    screenSize=newSize;
}

