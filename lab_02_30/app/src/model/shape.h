#ifndef SHAPE_H
#define SHAPE_H

#include <QPainter>


class Shape
{
public:
    virtual void draw(QPainter &p);
    virtual void rotate(const QPointF &center, float angle);
    virtual void move(const QVector2D &move_vect);
    virtual void scale(const QPointF &center, const QVector2D &scale_vect);
};

#endif // SHAPE_H
