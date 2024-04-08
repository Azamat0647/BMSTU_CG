#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "point2d.h"
#include <QtCharts>


class Rectangle
{
private:
    Point2D _topLeft, _topRight, _bottomRight, _bottomLeft;
public:
    Rectangle() = default;
    Rectangle(const QPointF &center, float width, float height);
    void draw(QChart *chart, const QPen &pen);
    void rotate(const QPointF &center, float angle);
    void move(const QVector2D &move_vect);
    void scale(const QPointF &center, const QVector2D &scale_vect);
};

#endif // RECTANGLE_H
