#ifndef CYRUSBECKCLIPPINGALGORITHM_H
#define CYRUSBECKCLIPPINGALGORITHM_H

#include "drawer.h"
#include "polygon.h"


class CyrusBeckClippingAlgorithm
{
public:
    CyrusBeckClippingAlgorithm();

    static void cuttOffLine(const QLine &line,
                            const Polygon &cutter,
                            QScopedPointer<QLine> &res);

    static QList<QLine> cuttOff(const QList<QLine> &lines,
                                const Polygon &cutter);

public:
    static QVector2D getNormal(const QVector2D &vect);
};

#endif // CYRUSBECKCLIPPINGALGORITHM_H
