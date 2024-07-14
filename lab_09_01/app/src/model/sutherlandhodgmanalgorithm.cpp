#include "sutherlandhodgmanalgorithm.h"
#include <QVector2D>
#include <QVector3D>

SutherlandHodgmanAlgorithm::SutherlandHodgmanAlgorithm()
{

}

Polygon SutherlandHodgmanAlgorithm::cutOffPolygon(Polygon polygon,
                                                  const Polygon &cutter)
{
    for (int ci = 0; ci < cutter.size(); ci++)
    {

        QPoint cp1 = cutter.point(ci);
        QPoint cp2 = (ci == cutter.size()-1) ?
                        cutter.point(0) : cutter.point(ci+1);
        QLine cutterEdge(cp1, cp2);

        Polygon res;
        for (int pi = 0; pi < polygon.size(); pi++)
        {
            QPoint p1 = polygon.point(pi);
            QPoint p2 = (pi == polygon.size()-1) ?
                            polygon.point(0) : polygon.point(pi+1);

            bool p1_visible = pointIsVisible(cutterEdge, p1);
            bool p2_visible = pointIsVisible(cutterEdge, p2);


            if (p1_visible and p2_visible)
                res << p2;
            else if (!p1_visible and p2_visible)
            {
                QScopedPointer<QPoint> inter;
                intersection(QLine(p1, p2), cutterEdge, inter);

                res << *inter;
                res << p2;
            }
            else if (p1_visible and !p2_visible)
            {
                QScopedPointer<QPoint> inter;
                intersection(QLine(p1, p2), cutterEdge, inter);
                res << *inter;
            }
        }
        polygon = res;
    }

    return polygon;
}

void SutherlandHodgmanAlgorithm::intersection(const QLine &line,
                                              const QLine &cutterEdge,
                                              QScopedPointer<QPoint> &res)
{
    QPointF p1 = line.p1(), p2 = line.p2();
    QPointF q1 = cutterEdge.p1(), q2 = cutterEdge.p2();

    QPointF pd = p2 - p1;
    QPointF qd = q2 - q1;

    if ((qd.x() == 0 and pd.x() == 0) or
        (qd.y() == 0 and pd.y() == 0) or
         qd.isNull() or pd.isNull())
        return;

    float t;
    if (pd.x() == 0)
    {
        t = (q1.y() - p1.y() + qd.y()*(p1.x() - q1.x())) / (pd.y()*qd.x());
    }
    else if (qd.y() == 0)
    {
        t = (q1.y() - p1.y()) / pd.y();
    }
    else
    {

        float D = qd.x() / qd.y();
        float W = pd.y() / pd.x();

        if (W*D == 1)
            return;

        t = (q1.x() - p1.x() + D*(p1.y() - q1.y()))/(pd.x()*(1 - W*D));
    }
    res.reset(new QPoint((p1 + (p2 - p1)*t).toPoint()));
}

bool SutherlandHodgmanAlgorithm::pointIsVisible(const QLine &l, const QPoint &p)
{
    QVector2D v1(l.p2() - l.p1());
    QVector2D v2(p - l.p1());

    return QVector3D::crossProduct(v1, v2).z() >= 0;
}

QList<Polygon>
SutherlandHodgmanAlgorithm::cutOff(const QList<Polygon> &polygons,
                                   const Polygon &cutter)
{
    Polygon cutterP(cutter);

    if (!cutterP.isConvex())
        throw QString("Отсекатель не выпуклый");

    QList<Polygon> res_polygons;
    for (const Polygon &p : polygons)
    {
        Polygon res = cutOffPolygon(p, cutterP);

        if (!res.isEmpty())
            res_polygons << res;
    }

    return res_polygons;
}
