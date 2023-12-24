#include "river.h"

River::River(QPointF p1, QPointF p2)
 {
    color = QColor(19,104,232);
    shape = {p1,
           p2,
           {p2.x() - 3 * sin(atan2(p2.y() - p1.y(), p2.x() - p1.x())),
            p2.y() + 3 * cos(atan2(p2.y() - p1.y(), p2.x() - p1.x()))},
           {p1.x() - 3 * sin(atan2(p2.y() - p1.y(), p2.x() - p1.x())),
            p1.y() + 3 * cos(atan2(p2.y() - p1.y(), p2.x() - p1.x()))}};
}
