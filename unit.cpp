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
    movable(false),orientation(0){

}



void Unit::selectUnit(QPoint point){

    if(shape.containsPoint(point, Qt::OddEvenFill)) {
        selected = !selected;
    }
}
int Unit::attack(Unit* enemy){
    if(enemy->health<=0){
        qDebug("enemy unit destroyed!");
        return 1;
    }
    else{
        enemy->health-=(attackPower-defensePower/100);
        qDebug("Unit attack to enemy unit! health->%i",enemy->health);
        return 0;
    }
}


void Unit::setTarget(QPoint point){

    if(selected){
        target={point.x(),point.y()};
        movable=true;
        angle = atan2(point.y() - shape.boundingRect().center().y(),
                      point.x()- shape.boundingRect().center().x());
        selected = false;
    }

}

void Unit::moveTo() {
        if (movable) {// if next
            if(collisionState==0){

            this->setPosition({newPosX, newPosY});
            }
            else {
                movable = selected = false; // other states
            }
        }


}
QPolygonF Unit::getNextPoly(){
    if(movable){
        double dx = target[0] - shape.boundingRect().center().x();
        double dy = target[1] - shape.boundingRect().center().y();
        double distance = sqrt(dx * dx + dy * dy);
        if (distance > speed) {

            newPosX = shape.boundingRect().center().x() + speed * cos(angle);
            newPosY = shape.boundingRect().center().y() + speed * sin(angle);
        } else {
            newPosX = target[0];
            newPosY = target[1];
            movable = selected = false; // if unit arrives at the target
        }
    }
    return QPolygonF() << QPointF(newPosX - width / 2, newPosY - height / 2)
                       << QPointF(newPosX + width / 2, newPosY - height / 2)
                       << QPointF(newPosX + width / 2, newPosY + height / 2)
                       << QPointF(newPosX - width / 2, newPosY + height / 2);
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
    //painter->save();
    painter->setOpacity(selected ? 0.2 : 1);
    painter->setPen(color.lighter(60));
    painter->setBrush(QBrush(color));
    painter->setRenderHint(QPainter::Antialiasing, true);
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

    // Draw rounded integer values for debug information
    /*painter->setPen(Qt::red);
    painter->setFont(QFont("Arial", 10));

    QPoint roundedPosition(static_cast<int>(shape[0].x()), static_cast<int>(shape[0].y()));
    QString debugText = QString("X: %1\nY: %2").arg(roundedPosition.x()).arg(roundedPosition.y());
    painter->drawText(roundedPosition, debugText);

    // Draw a 2px dot at the top-left corner
    painter->setPen(Qt::black);
    painter->setBrush(Qt::black);
    painter->drawEllipse(roundedPosition.x(), roundedPosition.y(), 2, 2);

    painter->restore();*/
}
