#ifndef POINT2D_H
#define POINT2D_H

#include <QVector2D>


class Point2D : public QPointF
{
public:
    using QPointF::QPointF;
    Point2D(const QPointF &point);
    void move(const QVector2D &move_vect);
    void rotate(const QPointF &center, float angle);
    void scale(const QPointF &center, const QVector2D &scale_vect);

};

#endif // POINT2D_H
