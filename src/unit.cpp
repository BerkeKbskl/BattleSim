#include "unit.h"

Unit::Unit(int x, int y, double width, double height):
    angle(M_PI/2),
    target(x,y),
    center(x,y),
    health(100),
    maxHealth(health),
    speed(1),
    selected(false),
    movable(false),
    width(width),
    height(height){

}

Unit::~Unit(){

}


void Unit::setSelection(bool exp){
    selected= exp;
}


void Unit::manualMove(QPointF point,QRectF border,QVector<Obstacle*> obstacles,QVector<Unit*> unit){
    bool isFieldEmpty=true;
    for (Unit *unit:unit){
        if(isFieldEmpty){isFieldEmpty=!unit->getCurrentPath().intersects(QRectF(point.x(),point.y(),width+5,height+5));}
    }
    for(Obstacle *obstacle:obstacles){
        if(isFieldEmpty){isFieldEmpty=!obstacle->getPath().intersects(QRectF(point.x(),point.y(),width+10,height+10));}
    }
    if(selected&&border.contains(point)&&isFieldEmpty){
    center=point;
    selected=false;
    }
}

int Unit::attack(Unit& enemy){

    if(enemy.health<=0){
        return 1;
    }
    else{
        enemy.health-=(attackPower);
        return 0;
    }
}

double Unit::getHealth() const{
    return health;
}


void Unit::setColor(const QColor color){
    this->color = color;
}

void Unit::setPosition(const QPointF v) {
    center = v;
}

bool Unit::selectUnit(const QPointF point){
    selected = getCurrentPath().contains(point) ? !selected : selected;
    return selected;
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

void Unit::moveTo(){
    if (movable) {
            // Less readable
            if ((target - center).manhattanLength() > speed) {
                center += QPointF(speed * cos(angle), speed * sin(angle));
            } else {
                stop();
            }
    }
}


QPainterPath Unit::getNextPath() const {

    // Pushes the current collider forward the angle
    QPointF translationVector =
        QPointF(center.x() + 8 * cos(angle),
                center.y() + 8 * sin(angle)) - center;

    QTransform rotationTransform;
    rotationTransform.translate(translationVector.x(),translationVector.y());
    return rotationTransform.map(getCurrentPath()) + Unit::getCurrentPath();
}


QPainterPath Unit::getCurrentPath() const
{
    // Returns the current collider
    QPainterPath ellipsePath;
    ellipsePath.addRect(center.x() - width / 2, center.y() - height / 2, width , height);

    QTransform rotationTransform;
    rotationTransform.translate(center.x(),center.y());

    rotationTransform.rotate(this->angle * 180 / (M_PI) + 90);
    rotationTransform.translate(-center.x(),-center.y());

    return rotationTransform.map(ellipsePath);
}

QPainterPath Unit::getAttackCollider() const
{
    return Unit::getNextPath();
}

void Unit::draw(QPainter* painter) {
    painter->save();
    painter->setOpacity(selected ? 0.2 : 1);
    painter->setPen(color.black());

    painter->setPen(color.lighter(60));

    painter->setRenderHint(QPainter::Antialiasing, true);

    if (!img.isNull()) {
        QImage resizedImage = img.scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        QTransform transform;
        transform.rotate(angle * 180 / M_PI + -90);
        resizedImage = resizedImage.transformed(transform, Qt::SmoothTransformation);

        painter->setRenderHint(QPainter::SmoothPixmapTransform, true);

        QPointF imageTopLeft = center - QPointF(resizedImage.width() / 2, resizedImage.height() / 2);

        // Draw the background with transparency
        painter->fillPath(getCurrentPath(),color);
        painter->drawImage(imageTopLeft, resizedImage);
    }

    // Draw health bar
    double healthBarWidth = 20;  // Adjust this value as needed
    double healthBarHeight = 5;  // Adjust this value as needed
    double healthBarX = center.x() - 20;
    double healthBarY = center.y() - healthBarHeight - 2 - 20;  // Adjust the offset as needed

    // Calculate the width based on the current health percentage
    double currentHealthWidth = healthBarWidth * (health / maxHealth);

    // Draw the background of the health bar
    painter->setBrush(Qt::red);
    painter->drawRect(healthBarX, healthBarY, healthBarWidth, healthBarHeight);

    // Draw the current health
    painter->setBrush(Qt::green);
    painter->drawRect(healthBarX, healthBarY, currentHealthWidth, healthBarHeight);

    painter->restore();
}
