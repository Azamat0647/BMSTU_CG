#ifndef FLOATINGHORIZONALGORITHM_H
#define FLOATINGHORIZONALGORITHM_H

#include "controller.h"
#include "point3d.h"


class FloatingHorizonAlgorithm
{
public:
    FloatingHorizonAlgorithm();

    static void draw(func_t func, range_t xrange, range_t zrange,
                     const QMatrix4x4 &matrix, Drawer &drawer);


private:

    static void drawLineByHorizon(const QPoint &p1, const QPoint &p2,
                                  QVector<int> &top, QVector<int> &bottom,
                                  Drawer &drawer);


    static void drawPointByHorizon(const QPoint &p,
                                  QVector<int> &top, QVector<int> &bottom,
                                  Drawer &drawer);


};

#endif // FLOATINGHORIZONALGORITHM_H
