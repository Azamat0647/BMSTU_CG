#ifndef CROSS_H
#define CROSS_H

#include <QtCharts>
#include "point2d.h"

class Cross
{
protected:
    Point2D _center, _a, _b;
public:
    Cross() = default;
    Cross(const QPointF &center, float width, float height);
    void draw(QChart *chart, const QPen &pen);
    void rotate(const QPointF &center, float angle);
    void move(const QVector2D &move_vect);
    void scale(const QPointF &center, const QVector2D &scale_vect);
};

#endif // CROSS_H
