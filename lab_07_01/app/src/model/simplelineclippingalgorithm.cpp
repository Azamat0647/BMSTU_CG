#include "simplelineclippingalgorithm.h"



int SimpleLineClippingAlgorithm::pointCode(const QPoint &point, const QRect &cutterRect)
{
    int code = 0b0000;

    if (point.x() < cutterRect.left()) code |= 0b0001;
    if (point.x() > cutterRect.right()) code |= 0b0010;
    if (point.y() < cutterRect.bottom()) code |= 0b0100;
    if (point.y() > cutterRect.top()) code |= 0b1000;

    return code;
}

bool SimpleLineClippingAlgorithm::checkLeftIntersect(const QPoint &Q,
                                                     const QRect &cutRect,
                                                     int i, double m,
                                                     QLine &resLine)
{
    if (Q.x() > cutRect.left())
        return false;

    bool res = false;

    int yp = m*(cutRect.left() - Q.x()) + Q.y();

    if (yp <= cutRect.top() and yp >= cutRect.bottom())
    {
        QPoint resPoint(cutRect.left(), yp);
        if (i == 1)
            resLine.setP1(resPoint);
        else
            resLine.setP2(resPoint);
        res = true;
    }
    return res;
}

bool SimpleLineClippingAlgorithm::checkRightIntersect(const QPoint &Q,
                                                      const QRect &cutRect,
                                                      int i, double m,
                                                      QLine &resLine)
{

    if (Q.x() < cutRect.right())
        return false;

    bool res = false;
    int yp = m*(cutRect.right() - Q.x()) + Q.y();

    if (yp <= cutRect.top() and yp >= cutRect.bottom())
    {
        QPoint resPoint(cutRect.right(), yp);
        if (i == 1)
            resLine.setP1(resPoint);
        else
            resLine.setP2(resPoint);
        res = true;
    }
    return res;
}

bool SimpleLineClippingAlgorithm::checkTopIntersect(const QPoint &Q,
                                                    const QRect &cutRect,
                                                    int i, double m,
                                                    QLine &resLine)
{
    if (Q.y() < cutRect.top())
        return false;

    bool res = false;
    int xp = (cutRect.top() - Q.y()) / m + Q.x();

    if (xp >= cutRect.left() and xp <= cutRect.right())
    {
        QPoint resPoint(xp, cutRect.top());
        if (i == 1)
            resLine.setP1(resPoint);
        else
            resLine.setP2(resPoint);
        res = true;
    }
    return res;
}

bool SimpleLineClippingAlgorithm::checkBottomIntersect(const QPoint &Q,
                                                       const QRect &cutRect,
                                                       int i, double m,
                                                       QLine &resLine)
{
    if (Q.y() > cutRect.bottom())
        return false;

    bool res = false;
    int xp = (cutRect.bottom() - Q.y()) / m + Q.x();

    if (xp >= cutRect.left() and xp <= cutRect.right())
    {
        QPoint resPoint(xp, cutRect.bottom());
        if (i == 1)
            resLine.setP1(resPoint);
        else
            resLine.setP2(resPoint);
        res = true;
    }

    return res;
}


void SimpleLineClippingAlgorithm::clipping(const QList<QLine> &lines,
                                           const QRect &cutterRect,
                                           Drawer &drawer)
{
    QRect cutter(cutterRect);
    if (cutter.bottom() > cutter.top())
    {
        cutter.setBottom(cutterRect.top());
        cutter.setTop(cutterRect.bottom());
    }

    for (const QLine &line : lines)
    {
        int T_1 = pointCode(line.p1(), cutter);
        int T_2 = pointCode(line.p2(), cutter);

        if (T_1 == 0 and T_2 == 0)
        {
            drawer.drawLine(line);
            continue;
        }
        else if ((T_1 & T_2) != 0)
            continue;

        bool flag = true;
        double m = 1e30;

        QLine resLine;
        QPoint Q, p1 = line.p1(), p2 = line.p2();

        int i = 1;
        if (T_1 == 0)
        {
            i = 2;
            resLine.setP1(p1);
        }
        else if (T_2 == 0)
        {
            i = 2;
            resLine.setP1(p2);
            std::swap(p1, p2);
        }

        for (;i <= 2; i++)
        {
            Q = (i == 1) ? p1 : p2;

            if (p1.x() != p2.x())
            {
                m = (p2.y() - p1.y()) / double(p2.x() - p1.x());

                if (checkLeftIntersect(Q, cutter, i, m, resLine) or
                        checkRightIntersect(Q, cutter, i, m, resLine))
                    continue;
            }

            if (m == 0)
                continue;

            if (checkTopIntersect(Q, cutter, i, m, resLine) or
                    checkBottomIntersect(Q, cutter, i, m, resLine))
                continue;
            else
                flag = false;

        }

        if (flag)
            drawer.drawLine(resLine);

    }
}
