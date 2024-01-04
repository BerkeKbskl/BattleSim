#include "artillery.h"

/**
 * @brief Constructs an Artillery object.
 *
 * This constructor initializes the Artillery object with default values for speed, health,
 * attack power, defense power, ammo, and image. It also loads the artillery image.
 */
Artillery::Artillery() : Unit() {
    speed = 2;
    health = 100;
    attackPower = 3;
    defensePower = 0;
    ammo = 150;
    img.load(":images/images/artillery.png");
    meleePower = 1;
}

/**
 * @brief Attacks an enemy unit.
 *
 * This function determines whether to perform a ranged or melee attack based on the
 * ammunition count. It then calls the base class attack method to calculate and apply
 * the damage.
 *
 * @param enemy The enemy unit to attack.
 * @return The damage dealt to the enemy unit.
 */
int Artillery::attack(Unit& enemy){
    if (!shoot())
        attackPower = meleePower;
        
    return Unit::attack(enemy);
}

/**
 * @brief Gets the attack collider path for the artillery unit.
 *
 * This function returns the QPainterPath representing the current attack collider
 * for the artillery unit. The collider is a rectangle in front of the unit when there
 * is ammunition available, otherwise, it is a smaller rectangle near the unit.
 *
 * @return The QPainterPath representing the attack collider.
 */
QPainterPath Artillery::getAttackCollider() const
{

    QPainterPath ellipsePath;
    if(ammo>0)
    ellipsePath.addRect(center.x() - width / 2 , center.y() - height / 2 -height * 3, width , height * 4);
    else
    ellipsePath.addRect(center.x() - width / 2, center.y() - height / 2 -8, width, height);

    QTransform rotationTransform;
    rotationTransform.translate(center.x(),center.y());

    rotationTransform.rotate(this->angle * 180 / (M_PI) + 90);
    rotationTransform.translate(-center.x(),-center.y());

    return rotationTransform.map(ellipsePath);
}

/**
 * @brief Performs a ranged attack, reducing ammunition.
 *
 * This function checks if ammunition is available. If so, it decrements the ammunition count
 * and returns true. Otherwise, it returns false.
 *
 * @return True if the artillery unit successfully shoots, false otherwise.
 */
bool Artillery::shoot() {

    if (ammo > 0) {
        ammo--;
        return true;
    } else {
        return false;
    }

}

/**
 * @brief Draws the artillery unit on the painter.
 *
 * This function calls the base class draw method to draw the unit shape and then
 * additionally draws the ammunition count in the middle of the shape.
 *
 * @param painter The QPainter object used for drawing.
 */
void Artillery::draw(QPainter* painter) {
    // Call the base class draw method to draw the unit shape
    Unit::draw(painter);

    painter->save();

    painter->setRenderHint(QPainter::Antialiasing, true);
    QPainterPath rotatedRectPath = getCurrentPath();

    // Calculate the position of the black rectangle on the right side
    double blackRectWidth = 20;  // Adjust this value as needed
    double blackRectHeight = height - 5;  // Match the height of the bounding rectangle
    double blackRectX = center.x() + height - blackRectWidth;  // Right side of the bounding rectangle
    double blackRectY = center.y() - blackRectHeight / 2;  // Align with the top of the bounding rectangle

    // Move the text to the bottom right corner
    blackRectY += blackRectHeight - 10;  // Adjust as needed

    // Draw the ammo count on the rotated black rectangle
    painter->setPen(Qt::black);
    QFont font("Arial", 10, QFont::Bold);  // Set the font to bold
    painter->setFont(font);
    QString ammoText = QString::number(ammo / 10);  // Assuming ammo is an integer variable

    // Draw the text on the rotated black rectangle
    painter->translate(center);
    painter->rotate(fmod(angle * 180 / M_PI,180)- 90);  // Apply the same rotation as the unit
    painter->translate(-center);

    painter->drawText(blackRectX-3, blackRectY, blackRectWidth, blackRectHeight-6, Qt::AlignCenter, ammoText);

    painter->restore();
}


