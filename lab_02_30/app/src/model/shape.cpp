#include "shape.h"

void Shape::move(const QVector2D &move_vect)
{
    _center.move(move_vect);
    for (int i = 0; i < basePoints.size(); i++)
    {
        basePoints[i].move(move_vect);
    }
}

void Shape::rotate(const QPointF &center, float angle)
{
    _center.rotate(center, angle);
    for (int i = 0; i < basePoints.size(); i++)
    {
        basePoints[i].rotate(center, angle);
    }
}

void Shape::scale(const QPointF &center, const QVector2D &scale_vect)
{
    _center.scale(center, scale_vect);
    for (int i = 0; i < basePoints.size(); i++)
    {
        basePoints[i].scale(center, scale_vect);
    }
}
