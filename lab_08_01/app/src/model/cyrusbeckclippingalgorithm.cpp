#include "cyrusbeckclippingalgorithm.h"
#include <QtNumeric>

CyrusBeckClippingAlgorithm::CyrusBeckClippingAlgorithm()
{

}


void CyrusBeckClippingAlgorithm::cuttOffLine(const QLine &line,
                                             const Polygon &cutter,
                                             QScopedPointer<QLine> &res)
{
    float tb = 0, te = 1;
    QVector2D D(line.p2() - line.p1());

    bool lineIsInvisible = false;

    for (int i = 0; i < cutter.size(); i++)
    {

        QLine edge(cutter.point(i),
                   (i == cutter.size()-1) ? cutter.point(0) : cutter.point(i+1));

        QVector2D Ni = getNormal(QVector2D(edge.p2() - edge.p1()));


        QVector2D W_i(line.p1() - edge.p1());

        float Wsc = QVector2D::dotProduct(W_i, Ni);
        float Dsc = QVector2D::dotProduct(D, Ni);

        if (qFuzzyIsNull(Dsc))
        {
            if (Wsc < 0)
                lineIsInvisible = true;
            continue;
        }

        float t = -Wsc / Dsc;

        if (Dsc > 0)
        {
            if (t > 1 and !qFuzzyCompare(1, t))
            {
                lineIsInvisible = true;
            }
            else
                tb = qMax(tb, t);
        }
        else
        {
            if (t < 0 and !qFuzzyIsNull(t))
            {
                lineIsInvisible = true;
            }
            else
                te = qMin(te, t);
        }
    }

    if (lineIsInvisible or tb > te)
        return;

    QPoint p1 = line.p1() + (D*tb).toPoint();
    QPoint p2 = line.p1() + (D*te).toPoint();

    res.reset(new QLine(p1, p2));
}

QList<QLine> CyrusBeckClippingAlgorithm::cuttOff(const QList<QLine> &lines,
                                                 const Polygon &cutter)
{
    QList<QLine> res_lines;

    Polygon cutterP(cutter);

    if (!cutterP.isConvex())
        throw QString("Отсекатель не выпуклый");

    int i = 0;
    for (const QLine &l : lines)
    {
        QScopedPointer<QLine> res(nullptr);
        cuttOffLine(l, cutterP, res);
        if (res)
            res_lines << *res;
    }

    return res_lines;
}


QVector2D CyrusBeckClippingAlgorithm::getNormal(const QVector2D &vect)
{
    float nx = 1;
    float ny;

    if (qFuzzyIsNull(vect.y()))
    {
        nx = 0;
        ny = 1;
    }
    else
        ny = -vect.x() / vect.y();

    QVector2D n(nx, ny);
    if (QVector3D::crossProduct(vect, n).z() < 0)
        n *= -1;

    return n;
}
