#include "artillery.h"
#include <iostream>

Artillery::Artillery() : Unit() {
    speed = 2;
    health=300;
    attackPower=35;
    defensePower = 15;
    ammo = 1000;
    img.load(":images/images/artillery.png");
}

int Artillery::attack(Unit& enemy){

    // Are they touching? You can't shoot what is in front of you.
    if (getNextPoly().intersects(enemy.shape))  {
        return Unit::attack(enemy);
    } else {
        qDebug("shooting from distance");
        // If from distance!
        while(shoot()) {
            if(enemy.health<=0){
                return 1;
            }
            else{
                enemy.health-=(attackPower-defensePower/100);
                return 0;
            }
        }
        return 0;
    }




}

QPolygonF Artillery::getNextCollider()
{


    QPolygonF nextPolygon(Unit::getNextPoly());

    // Calculate the current center of the polygon
    QPointF currentCenter = nextPolygon.boundingRect().center();

    // Scale the polygon by a factor of 2 based on its center
    for (int i = 0; i < nextPolygon.size(); ++i) {
        QPointF vector = nextPolygon[i] - currentCenter;
        nextPolygon[i] = currentCenter + 5 * vector;
    }

    return nextPolygon;


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
    QFont font("Arial", 12);
    painter->setFont(font);
    painter->setPen(Qt::black);

    // Calculate the position to display the ammo count in the middle of the shape
    QPointF textPosition = shape.boundingRect().center();
    textPosition -= QPointF(0, font.pixelSize() / 2); // Adjust for vertical alignment

    // Draw the ammo count
    QString ammoText = QString("Ammo: %1").arg(ammo);
    painter->drawText(textPosition, ammoText);
}


