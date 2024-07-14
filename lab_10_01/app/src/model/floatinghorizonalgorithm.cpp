#include "floatinghorizonalgorithm.h"

FloatingHorizonAlgorithm::FloatingHorizonAlgorithm()
{

}

void FloatingHorizonAlgorithm::draw(func_t func,
                                    range_t xrange,
                                    range_t zrange,
                                    const QMatrix4x4 &matrix,
                                    Drawer &drawer)
{
    QVector<int> top(drawer.imageWidth()+1);
    QVector<int> bottom(drawer.imageWidth()+1);

    for (int i = 0; i < drawer.imageWidth()+1; i++)
    {
        top[i] = 0;
        bottom[i] = drawer.imageHeight();
    }

    std::unique_ptr<QPoint> leftPreP, rightPreP;
    qreal z = zrange.to;

    while (z > zrange.from)
    {   
        auto preP = std::unique_ptr<QPoint>(nullptr);
        qreal x = xrange.from;
        QPoint curP;

        while (x < xrange.to)
        {
            qreal y = func(x, z);

            Point3D p(x, y, z);
            p.transform(matrix);
            curP = p.toQPoint();

            if (preP)
            {
                drawLineByHorizon(*preP, curP, top, bottom, drawer);
            }
            else
            {
                if (leftPreP)
                   drawLineByHorizon(*leftPreP, curP, top, bottom, drawer);
                leftPreP = std::make_unique<QPoint>(curP);
            }

            preP = std::make_unique<QPoint>(curP);
            x += xrange.step;
        }

        if (rightPreP)
            drawLineByHorizon(*rightPreP, curP, top, bottom, drawer);

        rightPreP = std::make_unique<QPoint>(curP);
        z -= zrange.step;
    }

}


void FloatingHorizonAlgorithm::drawLineByHorizon(const QPoint &p1,
                                                 const QPoint &p2,
                                                 QVector<int> &top,
                                                 QVector<int> &bottom,
                                                 Drawer &drawer)
{
    qreal dx = p2.x() - p1.x();
    qreal dy = p2.y() - p1.y();

    int lx = qAbs(dx), ly = qAbs(dy), l;

    if (lx > ly) l = lx;
    else l = ly;

    dx /= l; dy /= l;

    qreal x = p1.x(), y = p1.y();
    for (int i = 0; i <= l && !drawer.pixelOutOfRange(x, y); i++)
    {
        drawPointByHorizon(QPoint(qRound(x), qRound(y)), top, bottom, drawer);
        x += dx; y += dy;
    }
}

void FloatingHorizonAlgorithm::drawPointByHorizon(const QPoint &p,
                                                  QVector<int> &top,
                                                  QVector<int> &bottom,
                                                  Drawer &drawer)
{
    if (drawer.pixelOutOfRange(p.x(), p.y()))
        return;

    bool pVisible = false;
    if (p.y() > top[p.x()])
    {
        top[p.x()] = p.y();
        pVisible = true;
    }

    if (p.y() < bottom[p.x()])
    {
        bottom[p.x()] = p.y();
        pVisible = true;
    }

    if (pVisible)
        drawer.drawPoint(p);
}




