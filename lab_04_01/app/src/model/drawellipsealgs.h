#ifndef DRAWELLIPSEALGS_H
#define DRAWELLIPSEALGS_H

#include "drawer.h"

class DrawEllipseAlgs
{
  public:
    static void bresenham(const QPoint &center, int ra, int rb, Drawer &drawer);

    static void canonical(const QPoint &center, int ra, int rb, Drawer &drawer);

    static void parametric(const QPoint &center, int ra, int rb, Drawer &drawer);

    static void midpoint(const QPoint &center, int ra, int rb, Drawer &drawer);

    static void std(const QPoint &center, int ra, int rb, Drawer &drawer)
    {
        drawer.drawEllipse(center, ra, rb);
    };

  private:
    static inline void draw_1_4mirrored_points(int x, int y, const QPoint &center, Drawer &drawer)
    {
        int cx = center.x(), cy = center.y();

        drawer.drawPoint(cx + x, cy + y);
        drawer.drawPoint(cx - x, cy + y);
        drawer.drawPoint(cx + x, cy - y);
        drawer.drawPoint(cx - x, cy - y);
    }
};

#endif // DRAWELLIPSEALGS_H
