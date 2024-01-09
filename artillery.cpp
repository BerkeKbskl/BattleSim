#include "artillery.h"


Artillery::Artillery() : Unit() {
    speed = 0.2;
    health = 10;
    maxHealth=health;
    attackPower = 3;
    defensePower = 0;
    ammo = 50;
    img.load(":images/images/artillery.png");
    meleePower = 1;
}


int Artillery::attack(Unit& enemy){
    if (!shoot())
        attackPower = meleePower;
        
    return Unit::attack(enemy);
}


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
    QString ammoText = QString::number(ammo / 3);  // Assuming ammo is an integer variable

    // Draw the text on the rotated black rectangle
    painter->translate(center);
    painter->rotate(fmod(angle * 180 / M_PI,180)- 90);  // Apply the same rotation as the unit
    painter->translate(-center);

    painter->drawText(blackRectX-3, blackRectY, blackRectWidth, blackRectHeight-6, Qt::AlignCenter, ammoText);

    painter->restore();
}


