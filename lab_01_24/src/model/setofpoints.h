#ifndef SETOFPOINTS_H
#define SETOFPOINTS_H

#include <QList>
#include <QPoint>
#include <QRectF>

#define OK 0
#define ALREADY_EXIST_ERROR 1



class SetOfPoints
{
private:
    QList<QPointF> points;
    QRectF _boundingRect;

    void boundingRect_update();
public:
    SetOfPoints();
    int lenght();
    int add_point(QPointF point);
    int change_point(int index, QPointF new_point);
    void remove_point(int index);
    void clear_points();

    QRectF boundingRect();

    QPointF& operator[](unsigned index);
};

#endif // SETOFPOINTS_H
