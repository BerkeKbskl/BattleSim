#include "swamp.h"

Swamp::Swamp(QPointF p1, QPointF p2, QPointF p3, QPointF p4)
{
    color = QColor(112,226,226);
    shape = {p1,p2,p3,p4};
}
