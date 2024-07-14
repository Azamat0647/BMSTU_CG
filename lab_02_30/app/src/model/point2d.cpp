#include "point2d.h"
#include <QtMath>

Point2D::Point2D(const QPointF &point)
{
    setX(point.x());
    setY(point.y());
}

void Point2D::move(const QVector2D &move_vect)
{
    setX(x() + move_vect.x());
    setY(y() + move_vect.y());
}

void Point2D::rotate(const QPointF &center, float angle)
{
    float _x = x() - center.x();
    float _y = y() - center.y();

    float rad = qDegreesToRadians(angle);

    setX(center.x() + _x * qCos(rad) + _y * qSin(rad));
    setY(center.y() - _x * qSin(rad) + _y * qCos(rad));
}

void Point2D::scale(const QPointF &center, const QVector2D &scale_vect)
{
    setX(scale_vect.x() * x() + center.x() * (1 - scale_vect.x()));
    setY(scale_vect.y() * y() + center.y() * (1 - scale_vect.y()));
}
