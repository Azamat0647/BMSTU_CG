#ifndef DRAWCIRCLEALGS_H
#define DRAWCIRCLEALGS_H

#include "drawer.h"

class DrawCircleAlgs
{
  public:
    static void bresenham(const QPoint &center, int radius, Drawer &drawer);

    static void canonical(const QPoint &center, int radius, Drawer &drawer);

    static void parametric(const QPoint &center, int radius, Drawer &drawer);

    static void midpoint(const QPoint &center, int radius, Drawer &drawer);

    static void std(const QPoint &center, int radius, Drawer &drawer)
    {
        drawer.drawEllipse(center, radius, radius);
    };

  private:
    static inline void draw_1_8mirrored_points(int x, int y, const QPoint &center, Drawer &drawer)
    {
        int cx = center.x(), cy = center.y();

        drawer.drawPoint(cx + x, cy + y);
        drawer.drawPoint(cx - x, cy + y);
        drawer.drawPoint(cx + x, cy - y);
        drawer.drawPoint(cx - x, cy - y);

        drawer.drawPoint(cx + y, cy + x);
        drawer.drawPoint(cx - y, cy + x);
        drawer.drawPoint(cx + y, cy - x);
        drawer.drawPoint(cx - y, cy - x);
    }
};

#endif // DRAWCIRCLEALGS_H
