#include "polygon.h"

Polygon::Polygon(const QList<QPoint> &points) :
    QList<QPoint>(points)
{

}

QList<QLine> Polygon::edges()
{
    QList<QLine> edges;

    for (int i = 1; i < size(); i++)
    {
        edges << QLine(value(i-1), value(i));
    }

    edges << QLine(last(), first());

    return edges;
}
