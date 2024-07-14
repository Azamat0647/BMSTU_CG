#ifndef POLYGON_H
#define POLYGON_H

#include <QPolygon>
#include <QtCore>

class Polygon : public QPolygon
{
public:
    using QPolygon::QPolygon;

    bool isConvex();

private:
    bool edgesIntersects();
};

#endif // POLYGON_H
