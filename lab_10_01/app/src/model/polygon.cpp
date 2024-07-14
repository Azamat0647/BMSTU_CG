#include "polygon.h"

#include <QVector2D>
#include <QVector3D>

bool Polygon::isConvex()
{
    bool convex = true;
    int sign = 0;

    for (int i = 1; (i < size()) && convex; i++)
    {
        QPoint pi = point(i);
        QPoint p1 = point(i-1);
        QPoint p2 = (i == size()-1) ? point(0) : point(i+1);

        QVector2D edge1_vec(pi - p1);
        QVector2D edge2_vec(p2 - pi);

        int vecProd = QVector3D::crossProduct(edge1_vec, edge2_vec).z();

        if (!sign)
            sign = (vecProd < 0) ? -1 : 1;
        else if (sign * vecProd < 0)
            convex = false;
    }

    if (convex)
    {
        if (sign < 0)
            std::reverse(begin(), end());

        convex = !edgesIntersects();
    }

    return convex;
}



bool Polygon::edgesIntersects()
{
    if (size() <= 3)
        return false;

    bool inters = false;

    for (int i = 1; i < size() && !inters; i++)
    {
        QLineF l1(point(i-1), point(i));

        for (int j = i + 1; j < size() && !inters; j++)
        {
            if ((j == size()-1) && (i == 1))
                continue;

            QPoint p2 = (j == size()-1) ? point(0) : point(j+1);
            QLineF l2(point(j), p2);

            if (l1.intersects(l2, nullptr) == QLineF::BoundedIntersection)
                inters = true;
        }
    }

    return inters;
}

