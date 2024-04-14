#ifndef OBJECT2D_H
#define OBJECT2D_H

#include <QVector2D>

class Object2D
{
  public:
    virtual void move(const QVector2D &move_vect) = 0;
    virtual void rotate(const QPointF &center, float angle) = 0;
    virtual void scale(const QPointF &center, const QVector2D &scale_vect) = 0;
};

#endif // OBJECT2D_H
