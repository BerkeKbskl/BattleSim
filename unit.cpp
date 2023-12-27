#include "unit.h"
#include <iostream>


Unit::Unit(int x, int y, double width, double height)
    : shape({QPoint(x, y),
                QPoint(x + width, y),
                QPoint(x + width, y + height),
                QPoint(x, y + height)}),

    target(x, y),
    speed(0),
    health(100),
    angle(0),
    width(width),
    height(height),
    selected(false),
    movable(false),
    orientation(0),
    needHelp(false){

}



void Unit::selectUnit(QPointF point){

    if(shape.containsPoint(point, Qt::OddEvenFill)) {
        selected = !selected;
    }
}
bool Unit::isHelpNeed(){
    return this->needHelp;
}
QPointF Unit::getPosition(){
    return shape.boundingRect().center();
}
void Unit::rotate() {
    QTransform rotationTransform;
    rotationTransform.translate(this->shape.boundingRect().center().x(),
                                this->shape.boundingRect().center().y());
    //std::cout << unit->getAngle() << endl;
    rotationTransform.rotate(-this->orientation * 180 / (M_PI) + 90
                             + this->getAngle() * 180 / (M_PI) + 90);
    this->orientation = this->getAngle();
    rotationTransform.translate(-this->shape.boundingRect().center().x(),
                                -this->shape.boundingRect().center().y());
    this->shape = rotationTransform.map(this->shape);
}

int Unit::attack(Unit& enemy){
    enemy.needHelp = true;
    if(enemy.health<=0){
        return 1;
    }
    else{
        enemy.health-=(attackPower);
        return 0;
    }
}


void Unit::setTarget(QPointF point)
{
    if (selected) {
        target = {point.x(), point.y()};
        movable = true;
        angle = atan2(point.y() - shape.boundingRect().center().y(),
                      point.x() - shape.boundingRect().center().x());
        selected = false;
    }
}

void Unit::moveTo()
{
    if (movable) { // if next
        if (collisionState == 0) {
            this->setPosition({newPosX, newPosY});
        } else {
            movable = selected = false; // other states
        }
    }
}

QPolygonF Unit::getNextPoly()
{
    if (movable) {
        double dx = target.x() - shape.boundingRect().center().x();
        double dy = target.y() - shape.boundingRect().center().y();

        double distance = sqrt(dx * dx + dy * dy);
        if (distance > speed) {
            newPosX = shape.boundingRect().center().x() + speed * cos(angle);
            newPosY = shape.boundingRect().center().y() + speed * sin(angle);
            // adjusts...
        } else {
            newPosX = target.x();
            newPosY = target.y();
            movable = selected = false; // if unit arrives at the target
        }
    }


    QPolygonF nextPolygon(shape);

    QPointF v = {newPosX, newPosY};
    // Calculate the current center of the shape
    QPointF currentCenter = shape.boundingRect().center();
    // Calculate the translation vector to move the center to the new position
    QPointF translationVector = v - currentCenter;
    // Translate the shape using the calculated translation vector
    nextPolygon.translate(translationVector);

    return nextPolygon;


}

QPolygonF Unit::getNextCollider()
{
    return getNextPoly();
}


void Unit::setCollisionState(int index) {
    collisionState=index;
}


void Unit::setPosition(vector<double> w) {
    QPointF v = {w[0],w[1]};
    // Calculate the current center of the shape
    QPointF currentCenter = shape.boundingRect().center();
    // Calculate the translation vector to move the center to the new position
    QPointF translationVector = v - currentCenter;
    // Translate the shape using the calculated translation vector
    shape.translate(translationVector);
}

double Unit::getAngle() {
    return angle;
}


void Unit::draw(QPainter* painter) {
    painter->save();
    painter->setOpacity(selected ? 0.2 : 1);
    painter->setPen(color.lighter(60));
    //painter->setBrush(QBrush(color));
    painter->setRenderHint(QPainter::Antialiasing, true);

    QLinearGradient gradient(shape.boundingRect().topLeft(), shape.boundingRect().bottomLeft());
    gradient.setColorAt(0, color);          // Top color
    gradient.setColorAt(1, color.darker(20));  // Darker shade at the bottom

    painter->setBrush(gradient);

    // Draw the unit's shape
    painter->drawPolygon(shape);

    if (!img.isNull()) {
        QImage resizedImage = img.scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

        QTransform transform;
        transform.rotate(orientation * 180 / M_PI);
        resizedImage = resizedImage.transformed(transform, Qt::SmoothTransformation);

        painter->setRenderHint(QPainter::SmoothPixmapTransform, true);

        painter->drawImage(shape.boundingRect().topLeft().x(),
                           shape.boundingRect().topLeft().y(),
                           resizedImage);
    }

    // Draw health bar
    double healthBarWidth = width;  // Adjust this value as needed
    double healthBarHeight = 5;     // Adjust this value as needed
    double healthBarX = shape.boundingRect().topLeft().x();
    double healthBarY = shape.boundingRect().topLeft().y() - healthBarHeight - 2;  // Adjust the offset as needed

    // Calculate the width based on the current health percentage
    double currentHealthWidth = healthBarWidth * (health / 100.0);

    // Draw the background of the health bar
    //painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    painter->drawRect(healthBarX, healthBarY, healthBarWidth, healthBarHeight);

    // Draw the current health
    painter->setBrush(Qt::green);
    painter->drawRect(healthBarX, healthBarY, currentHealthWidth, healthBarHeight);



    painter->restore();
}

