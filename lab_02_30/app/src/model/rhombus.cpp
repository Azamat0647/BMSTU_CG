#include "rhombus.h"

Rhombus::Rhombus(const QPointF &center, float width, float height) : Shape(center)
{
    basePoints.append(QPoint(center.x() + width / 2, center.y()));
    basePoints.append(QPoint(center.x(), center.y() - height / 2));
}

void Rhombus::draw(Drawer &drawer)
{
    QList<Point2D> points(basePoints);

    const QPointF &a = basePoints[0];
    const QPointF &b = basePoints[1];

    points.append(_center - (a - _center));
    points.append(_center - (b - _center));

    drawer.drawPolygon(points);
}
