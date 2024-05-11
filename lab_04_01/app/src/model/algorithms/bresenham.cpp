#include "../drawcirclealgs.h"
#include "../drawellipsealgs.h"

void DrawCircleAlgs::bresenham(const QPoint &center, int radius, Drawer &drawer)
{
    int x = 0, y = radius;
    double delta = 2 * (1 - radius);

    draw_1_8mirrored_points(x, y, center, drawer);

    while (x < y)
    {
        if (delta < 0)
        {
            double temp = 2 * (delta + y) - 1;
            ++x;
            if (temp > 0)
            {
                --y;
                delta += 2 * (x - y + 1);
            }
            else
                delta += 2 * x + 1;
        }
        else
        {
            double temp = 2 * (delta - x) - 1;
            --y;
            if (temp < 0)
            {
                ++x;
                delta += 2 * (x - y + 1);
            }
            else
                delta -= 2 * y - 1;
        }

        draw_1_8mirrored_points(x, y, center, drawer);
    }
}

void DrawEllipseAlgs::bresenham(const QPoint &center, int ra, int rb, Drawer &drawer)
{
    int x = 0, y = rb;

    double delta = rb * rb - ra * ra * (2 * rb + 1);

    double pa = ra * ra, pb = rb * rb;

    while (y >= 0)
    {
        draw_1_4mirrored_points(x, y, center, drawer);

        if (delta < 0)
        {
            double temp = 2 * delta + pa * (2 * y - 1);
            ++x;
            delta += pb * (2 * x + 1);
            if (temp > 0)
            {
                --y;
                delta += pa * (-2 * y + 1);
            }
        }
        else if (0 == delta)
        {
            ++x;
            --y;
            delta += pb * (2 * x + 1) + (1 - 2 * y) * pa;
        }
        else
        {
            double temp = 2 * delta + pb * (-2 * x - 1);
            --y;
            delta += pa * (-2 * y + 1);
            if (temp < 0)
            {
                ++x;
                delta += pb * (2 * x + 1);
            }
        }
    }
}
