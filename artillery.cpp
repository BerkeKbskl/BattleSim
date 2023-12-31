#include "artillery.h"
#include <iostream>

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

    // Draw ammo count in the middle of the shape
    QFont font("Arial", 8);
    painter->setFont(font);
    painter->setPen(Qt::black);

    // Calculate the position to display the ammo count in the middle of the shape
    QPointF textPosition = center;
    textPosition -= QPointF(0, font.pixelSize() / 2); // Adjust for vertical alignment

    //painter->drawPolygon(getNextCollider());

    // Draw the ammo count
    QString ammoText = QString("%1").arg(ammo);
    painter->drawText(textPosition, ammoText);
}


