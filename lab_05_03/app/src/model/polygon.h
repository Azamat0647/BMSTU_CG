#ifndef POLYGON_H
#define POLYGON_H

#include <QtCore>

class Polygon : public QList<QPoint>
{
public:
    Polygon() = default;
    Polygon(const QList<QPoint> &points);

    QList<QLine> edges();
};

#endif // POLYGON_H
