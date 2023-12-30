#include "unit.h"

Unit::Unit(int x, int y, double width, double height)
    :
    center(x,y),
    target(x,y),
    speed(1),
    health(100),
    angle(M_PI/2),
    width(width),
    height(height),
    selected(false),
    movable(false),

    needHelp(false),
    helpAssigned(false){

}


bool Unit::isHelpNeed()
{
    return this->needHelp;
}

// -------------------------------------------------------------------


int Unit::attack(Unit& enemy){

    stop();

    enemy.needHelp = true;
    if(enemy.health<=0){
        return 1;
    }
    else{
        enemy.health-=(attackPower);
        return 0;
    }
}

int Unit::getHealth(){
    return health;
}

void Unit::setColor(const QColor color){
    this->color = color;
}

void Unit::setPosition(const QPointF v) {
    center = v;
}

void Unit::selectUnit(const QPointF point){
    selected = getCurrentPath().contains(point) ? !selected : selected;
}

QPointF Unit::getPosition() const {
    return center;
}

void Unit::stop(){

    target = center;
    movable = false;
}

void Unit::setTarget(const QPointF point)
{
    if (selected) { // should be able to set a target despite not being selected
        target = point;
        movable = true;
        selected = false;
        angle = atan2(point.y() - center.y(), point.x() - center.x());
    }

}

void Unit::moveTo()
{
    if (movable) {
            // Less readable
            if ((target - center).manhattanLength() > speed) {
                center += QPointF(speed * cos(angle), speed * sin(angle));
            } else {
                stop();
            }
    }
}

QPainterPath Unit::getNextPath() const
{
    // Pushes the current collider forward the angle
    QPointF translationVector =
        QPointF(center.x() + 8 * cos(angle),
                center.y() + 8 * sin(angle)) - center;

    QTransform rotationTransform;
    rotationTransform.translate(translationVector.x(),translationVector.y());
    return rotationTransform.map(getCurrentPath());
}

QPainterPath Unit::getCurrentPath() const
{
    // Returns the current collider
    QPainterPath ellipsePath;
    ellipsePath.addEllipse(center, width / 2 + 4, height / 4 + 4);

    QTransform rotationTransform;
    rotationTransform.translate(center.x(),center.y());

    rotationTransform.rotate(this->angle * 180 / (M_PI) + 90);
    rotationTransform.translate(-center.x(),-center.y());

    return rotationTransform.map(ellipsePath);
}

void Unit::draw(QPainter* painter) {
    painter->save();
    painter->setOpacity(selected ? 0.2 : 1);
    painter->setPen(color.black());

    painter->drawPath(getCurrentPath());

    painter->setPen(color.red());

    painter->drawPath(getNextPath());
    painter->setPen(color.lighter(60));

    painter->setRenderHint(QPainter::Antialiasing, true);


    if (!img.isNull()) {
        QImage resizedImage = img.scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

        QTransform transform;
        transform.rotate(angle * 180 / M_PI + -90);
        resizedImage = resizedImage.transformed(transform, Qt::SmoothTransformation);

        painter->setRenderHint(QPainter::SmoothPixmapTransform, true);

        QPointF imageTopLeft = center - QPointF(resizedImage.width() / 2, resizedImage.height() / 2);
        painter->drawImage(imageTopLeft, resizedImage);

    }

    // Draw health bar
    double healthBarWidth = 20;  // Adjust this value as needed
    double healthBarHeight = 5;     // Adjust this value as needed
    double healthBarX = center.x() - 20;
    double healthBarY = center.y() - healthBarHeight - 2 - 20;  // Adjust the offset as needed

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

