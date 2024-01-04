#include "unit.h"

Unit::Unit(int x, int y, double width, double height):
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
void Unit::setSelection(bool exp){
    selected= exp;
}

bool Unit::isHelpNeed()
{
    return this->needHelp;
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

void Unit::setSelected(bool b) {
    selected=b;
}
// -------------------------------------------------------------------

/**
 * @brief Attack another unit.
 *
 * Marks the attacked unit as needing help and decreases its health based on the
 * attack power. Returns 1 if the enemy unit's health is depleted; otherwise, 0.
 *
 * @param enemy The unit to be attacked.
 * @return 1 if the enemy unit's health is depleted; otherwise, 0.
 */
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

/**
 * @brief Get the current health of the unit.
 *
 * @return The current health value of the unit.
 */
int Unit::getHealth() const{
    return health;
}

/**
 * @brief Set the color of the unit.
 *
 * @param color The color to set for the unit.
 */
void Unit::setColor(const QColor color){
    this->color = color;
}

/**
 * @brief Set the position of the unit.
 *
 * @param v The position to set for the unit.
 */
void Unit::setPosition(const QPointF v) {
    center = v;
}

/**
 * @brief Unit::selectUnit
 * @param point
 */
bool Unit::selectUnit(const QPointF point){
    selected = getCurrentPath().contains(point) ? !selected : selected;
    return selected;
}

/**
 * @brief Get the current position of the unit.
 *
 * @return The current position of the unit as a QPointF.
 */
QPointF Unit::getPosition() const {
    return center;
}

/**
 * @brief Stop the unit's movement and set the target position to the current position.
 */
void Unit::stop(){
    target = center;
    movable = false;
}

/**
 * @brief Set the target position for the unit to move towards.
 *
 * If the unit is selected, the target position is set, and the unit becomes movable.
 * The unit's angle is also updated based on the new target position.
 *
 * @param point The target position for the unit.
 */
void Unit::setTarget(const QPointF point)
{
    if (selected) { // should be able to set a target despite not being selected
        target = point;
        movable = true;
        selected = false;
        angle = atan2(point.y() - center.y(), point.x() - center.x());
    }

}

/**
 * @brief Move the unit towards its target position.
 *
 * If the unit is movable, it is moved towards the target position. If the distance
 * to the target is less than the speed, the unit stops meaning it arrived..
 */
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

/**
 * @brief Get the next path of the unit after pushing the current collider forward the angle.
 *
 * This function calculates the next path of the unit by pushing the current collider forward
 * along the current angle. It uses a translation vector to move the collider and then applies
 * rotation to obtain the final path.
 *
 * @return The next QPainterPath representing the updated collider path.
 */
QPainterPath Unit::getNextPath() const {

    // Pushes the current collider forward the angle
    QPointF translationVector =
        QPointF(center.x() + 8 * cos(angle),
                center.y() + 8 * sin(angle)) - center;

    QTransform rotationTransform;
    rotationTransform.translate(translationVector.x(),translationVector.y());
    return rotationTransform.map(getCurrentPath()) + Unit::getCurrentPath();
}

/**
 * @brief Get the current path of the unit's collider.
 *
 * This function returns the current path of the unit's collider, which is an ellipse path
 * transformed by translation and rotation based on the unit's center, width, height, and angle.
 *
 * @return The current QPainterPath representing the unit's collider.
 */
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

/**
 * @brief Get the attack collider path of the unit.
 *
 * This function returns the attack collider path, which is the next path of the unit.
 *
 * @return The attack collider path as a QPainterPath.
 */
QPainterPath Unit::getAttackCollider() const
{
    return Unit::getNextPath();
}

/**
 * @brief Draw the unit on a QPainter.
 *
 * This function draws the unit on the provided QPainter, considering its current state,
 * position, and appearance.
 *
 * @param painter The QPainter on which to draw the unit.
 */
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
    double currentHealthWidth = healthBarWidth * (health / 100.0);

    // Draw the background of the health bar
    painter->setBrush(Qt::red);
    painter->drawRect(healthBarX, healthBarY, healthBarWidth, healthBarHeight);

    // Draw the current health
    painter->setBrush(Qt::green);
    painter->drawRect(healthBarX, healthBarY, currentHealthWidth, healthBarHeight);

    painter->restore();
}
