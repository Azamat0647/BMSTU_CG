#ifndef FIGURE_H
#define FIGURE_H

#include "cross.h"
#include "ellipse.h"
#include "point2d.h"
#include "rectangle.h"
#include "rhombus.h"
#include <QPainter>

class Figure : virtual public Shape
{
  private:
    Ellipse centerCircle;
    Cross centerCross;
    Rectangle bodyRect;
    Rhombus rhombus;
    Ellipse leftArc;
    Ellipse rightArc;

  public:
    Figure() = default;
    Figure(const QPointF &center, float width, float height);
    void draw(Drawer &drawer) override;
    void rotate(const QPointF &center, float angle) override;
    void move(const QVector2D &move_vect) override;
    void scale(const QPointF &center, const QVector2D &scale_vect) override;
};

#endif // FIGURE_H
