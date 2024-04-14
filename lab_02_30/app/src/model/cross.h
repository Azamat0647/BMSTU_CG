#ifndef CROSS_H
#define CROSS_H

#include "shape.h"

class Cross : virtual public Shape
{
  public:
    Cross() = default;
    Cross(const QPointF &center, float width, float height);
    void draw(Drawer &drawer) override;
};

#endif // CROSS_H
