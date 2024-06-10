#ifndef SUTHERLANDHODGMANALGORITHM_H
#define SUTHERLANDHODGMANALGORITHM_H

#include "polygon.h"

class SutherlandHodgmanAlgorithm
{
public:
    SutherlandHodgmanAlgorithm();
    static QList<Polygon> cutOff(const QList<Polygon> &polygons, const Polygon &cutter);

private:
    static Polygon cutOffPolygon(Polygon polygon,
                                 const Polygon &cutter);

    static bool pointIsVisible(const QLine &l, const QPoint &p);

    static void intersection(const QLine &line, const QLine &cutterEdge,
                             QScopedPointer<QPoint> &res);
};

#endif // SUTHERLANDHODGMANALGORITHM_H
