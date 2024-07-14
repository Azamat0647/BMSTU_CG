#include "cross.h"

Cross::Cross(const QPointF &center, float width, float height) : Shape(center)
{
    basePoints.append(Point2D(center.x() + width / 2, center.y()));
    basePoints.append(Point2D(center.x(), center.y() - height / 2));
}

void Cross::draw(Drawer &drawer)
{
    const QPointF &a = basePoints[0];
    const QPointF &b = basePoints[1];

    drawer.drawLine(a, _center - (a - _center));
    drawer.drawLine(b, _center - (b - _center));
}
