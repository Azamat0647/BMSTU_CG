#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "shape.h"

class Rhombus : virtual public Shape
{
  public:
    Rhombus() = default;
    Rhombus(const QPointF &center, float width, float height);
    void draw(Drawer &drawer) override;
};

#endif // RHOMBUS_H
