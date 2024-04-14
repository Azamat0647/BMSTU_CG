#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Rectangle : virtual public Shape
{
  public:
    Rectangle() = default;
    Rectangle(const QPointF &center, float width, float height);
    void draw(Drawer &drawer) override;
};

#endif // RECTANGLE_H
