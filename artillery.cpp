#include "artillery.h"
#include <iostream>

Artillery::Artillery() : Unit() {
    speed = 2;
    health = 100;
    attackPower = 3;
    defensePower = 0;
    ammo = 150;
    img.load(":images/images/artillery.png");
    meleePower = 1;
}

int Artillery::attack(Unit& enemy){
    if (!shoot())
        attackPower = meleePower;
        
    return Unit::attack(enemy);

    
    // Bullets?
}

QPainterPath Artillery::getAttackCollider() const
{
    // Returns the current collider
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


bool Artillery::shoot() {

    if (ammo > 0) {
        ammo--;
        return true;
    } else {
        return false;
    }

}

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


