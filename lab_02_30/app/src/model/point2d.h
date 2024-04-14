#ifndef POINT2D_H
#define POINT2D_H

#include "object2d.h"

class Point2D : public QPointF, virtual public Object2D
{
  public:
    using QPointF::QPointF;
    Point2D(const QPointF &point);
    void move(const QVector2D &move_vect) override;
    void rotate(const QPointF &center, float angle) override;
    void scale(const QPointF &center, const QVector2D &scale_vect) override;
};

#endif // POINT2D_H
