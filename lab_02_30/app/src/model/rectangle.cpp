#include "rectangle.h"

Rectangle::Rectangle(const QPointF &center, float width, float height) : Shape(center)
{
    basePoints.append(Point2D(center.x() - width / 2, center.y() - height / 2));
    basePoints.append(Point2D(center.x() - width / 2, center.y() + height / 2));
    basePoints.append(Point2D(center.x() + width / 2, center.y() + height / 2));
    basePoints.append(Point2D(center.x() + width / 2, center.y() - height / 2));
}

void Rectangle::draw(Drawer &drawer)
{
    drawer.drawPolygon(basePoints);
}
