#ifndef FIGURE_H
#define FIGURE_H

#include <QPainter>
#include "point2d.h"
#include "ellipse.h"
#include "rhombus.h"
#include "cross.h"
#include "rectangle.h"

class Figure
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
    void draw(QChart *chart);
    void rotate(const QPointF &center, float angle);
    void move(const QVector2D &move_vect);
    void scale(const QPointF &center, const QVector2D &scale_vect);
};

#endif // FIGURE_H
