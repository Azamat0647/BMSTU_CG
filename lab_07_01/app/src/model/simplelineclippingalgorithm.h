#ifndef SIMPLELINECLIPPINGALGORITHM_H
#define SIMPLELINECLIPPINGALGORITHM_H

#include "drawer.h"

class SimpleLineClippingAlgorithm
{
public:
    static void clipping(const QList<QLine> &lines,
                  const QRect &cutterRect, Drawer &drawer);

private:
    static int pointCode(const QPoint &point, const QRect &cutterRect);
    static bool checkLeftIntersect(const QPoint &Q,
                                   const QRect &cutRect,
                                   int i, double m,
                                   QLine &resLine);
    static bool checkRightIntersect(const QPoint &Q,
                                    const QRect &cutRect,
                                    int i, double m,
                                    QLine &resLine);
    static bool checkTopIntersect(const QPoint &Q,
                                  const QRect &cutRect,
                                  int i, double m,
                                  QLine &resLine);
    static bool checkBottomIntersect(const QPoint &Q,
                                     const QRect &cutRect,
                                     int i, double m,
                                     QLine &resLine);
};

#endif // SIMPLELINECLIPPINGALGORITHM_H
