#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSize>

/**
 * @brief The Settings class represents the configuration settings for a game.
 *
 * This class provides methods to get and set the scale and screen size for the game.
 */
class Settings
{
public:

    /**
     * @brief Constructor for the Settings class.
     */
    Settings();

    /**
     * @brief Gets the scale factor used in the game.
     * @return The current scale factor.
     */
    double getScale();

    /**
     * @brief Sets the scale factor to be used in the game.
     * @param scale The new scale factor to be set.
     */
    void setScale(double scale);

    /**
     * @brief Gets the screen size used in the game.
     * @return The current screen size.
     */
    QSize getScreenSize();

    /**
     * @brief Sets the screen size to be used in the game.
     * @param screenSize The new screen size to be set.
     */
    void setScreenSize(QSize screenSize);

private:
    double scale; ///< The scale factor used in the game.
    QSize screenSize; ///< The screen size used in the game.

};

#endif // SETTINGS_H

