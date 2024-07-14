#include "../drawcirclealgs.h"
#include "../drawellipsealgs.h"

void DrawCircleAlgs::midpoint(const QPoint &center, int radius, Drawer &drawer)
{
    int x = radius, y = 0;

    int delta = 1 - radius;

    while (x > y)
    {
        draw_1_8mirrored_points(x, y, center, drawer);
        ++y;

        if (delta > 0)
        {
            --x;
            delta -= 2 * x + 1;
        }

        delta += 2 * y + 1;
    }
}

void DrawEllipseAlgs::midpoint(const QPoint &center, int ra, int rb, Drawer &drawer)
{
    int x = 0, y = rb;

    int pa = ra * ra, pb = rb * rb;

    double delta = pb - pa * rb + 0.25 * pa;
    int dx = 2 * pb * x, dy = 2 * pa * y;

    while (dx < dy)
    {
        draw_1_4mirrored_points(x, y, center, drawer);
        ++x;
        dx += 2 * rb * rb;

        if (delta >= 0)
        {
            --y;
            dy -= 2 * pa;
            delta -= dy;
        }

        delta += dx + pb;
    }

    delta = pb * (x + 0.5) * (x + 0.5) + pa * (y - 1) * (y - 1) - pa * pb;

    while (y >= 0)
    {
        draw_1_4mirrored_points(x, y, center, drawer);

        --y;
        dy -= 2 * pa;

        if (delta <= 0)
        {
            ++x;
            dx += 2 * pb;
            delta += dx;
        }

        delta -= dy - pa;
    }
}
