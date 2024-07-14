#ifndef SHAPE_H
#define SHAPE_H

#include "drawer.h"
#include "point2d.h"
#include <QPainter>

class Shape : virtual public Object2D
{
  protected:
    Point2D _center;
    QList<Point2D> basePoints;

  public:
    Shape() = default;
    explicit Shape(const QPointF &center) : _center(center){};
    virtual void draw(Drawer &drawer) = 0;
    void rotate(const QPointF &center, float angle) override;
    void move(const QVector2D &move_vect) override;
    void scale(const QPointF &center, const QVector2D &scale_vect) override;
};

#endif // SHAPE_H
