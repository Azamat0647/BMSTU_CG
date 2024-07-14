#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "shape.h"

class Ellipse : virtual public Shape
{
  private:
    float _startAngle, _endAngle;

  public:
    Ellipse() = default;
    Ellipse(const QPointF &center, float a, float b, float startAngle = 0, float endAngle = M_PI * 2);
    void draw(Drawer &drawer) override;
};

#endif // ELLIPSE_H
