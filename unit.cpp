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
    orientation(0),
    width(width),
    height(height),
    selected(false),
    movable(false),

    needHelp(false),
    helpAssigned(false){

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


bool Unit::isHelpNeed(){
    return this->needHelp;
}


void Unit::rotate() {
    QTransform rotationTransform;
    rotationTransform.translate(this->shape.boundingRect().center().x(),
                                this->shape.boundingRect().center().y());

    rotationTransform.rotate(- this->orientation * 180 / (M_PI) + 90
                             + this->angle * 180 / (M_PI) + 90);
    orientation = angle;
    rotationTransform.translate(-this->shape.boundingRect().center().x(),
                                -this->shape.boundingRect().center().y());
    this->shape = rotationTransform.map(this->shape);
}


void Unit::selectUnit(QPointF point){

    if(shape.containsPoint(point, Qt::OddEvenFill)) {
        selected = !selected;
    }
}

QPointF Unit::getPosition(){
    return shape.boundingRect().center();
}

void Unit::setTarget(QPointF point)
{
    if (selected) {
        target = point;
        movable = true;
        selected = false;
        QPointF center = shape.boundingRect().center();
        angle = atan2(point.y() - center.y(), point.x() - center.x());

    }


}

void Unit::moveTo()
{
    if (movable) {
        if (collisionState == 0) {
            QPointF center = shape.boundingRect().center();
            double dx = target.x() - center.x();
            double dy = target.y() - center.y();

            double distance = sqrt(dx * dx + dy * dy);
            if (distance > speed) {
                newPosX = center.x() + speed * cos(angle);
                newPosY = center.y() + speed * sin(angle);

            } else {
                newPosX = target.x();
                newPosY = target.y();
                movable = selected = false; // If the unit arrives at the target
            }

            this->setPosition({newPosX, newPosY});
        } else {
            movable = selected = false; // Handle other states
        }
    }


}

QPolygonF Unit::getNextPoly()
{
    // Returns next polygon
    QPolygonF nextPolygon(shape);
    QPointF translationVector =
        QPointF(shape.boundingRect().center().x() + 2 * cos(angle),
                shape.boundingRect().center().y() + 2 * sin(angle)) - shape.boundingRect().center();
    nextPolygon.translate(translationVector);

    return nextPolygon;
}

QPainterPath Unit::getNextPath()
{
    // Returns next QPainterPath representing an ellipse
    QPointF center = shape.boundingRect().center();
    QPainterPath ellipsePath;
    ellipsePath.addEllipse(center, width, height);


    QTransform rotationTransform;
    rotationTransform.translate(this->shape.boundingRect().center().x(),
                                this->shape.boundingRect().center().y());

    rotationTransform.rotate(90);
    rotationTransform.translate(-this->shape.boundingRect().center().x(),
                                -this->shape.boundingRect().center().y());

    return rotationTransform.map(ellipsePath);
}



QPolygonF Unit::getNextCollider(){
    return getNextPoly();
}


void Unit::setCollisionState(int index) {
    collisionState=index;
}


void Unit::setPosition(QPointF v) {
    shape.translate(v - shape.boundingRect().center());
}


void Unit::draw(QPainter* painter) {
    painter->save();
    painter->setOpacity(selected ? 0.2 : 1);
    painter->setPen(color.black());

    painter->drawPolygon(getNextCollider());
    painter->drawPolygon(getNextPoly());
    painter->drawPath(getNextPath());
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
        transform.rotate(angle * 180 / M_PI);
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

