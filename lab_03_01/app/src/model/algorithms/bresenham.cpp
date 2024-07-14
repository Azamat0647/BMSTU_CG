#include "../drawlinealgorithms.h"

#include <cmath>

int32_t DrawLineAlgorithms::bresenham_int(const QLine &line, Drawer &drawer, bool display, bool steps)
{
    int ax = line.p1().x(), ay = line.p1().y();
    int bx = line.p2().x(), by = line.p2().y();

    int dx = bx - ax, dy = by - ay;

    int xsign = sign(dx), ysign = sign(dy);

    dx = std::abs(dx), dy = std::abs(dy);

    int change = 0;
    if (dy >= dx)
    {
        std::swap(dx, dy);
        change = 1;
    }

    int m = 2 * dy, m1 = 2 * dx;
    int e = m - dx;

    int x = ax, y = ay;
    int step = 1, x_buf = x, y_buf = y;

    for (int i = 0; i <= dx; i++)
    {
        if (display)
            drawer.drawPoint(x, y);

        if (e >= 0)
        {
            if (1 == change)
                x += xsign;
            else
                y += ysign;
            e -= m1;
        }
        if (e <= 0)
        {
            if (1 == change)
                y += ysign;
            else
                x += xsign;
            e += m;
        }

        if (!steps)
            continue;

        if (x_buf != x && y_buf != y)
            step++;

        x_buf = x;
        y_buf = y;
    }

    return step;
}

int32_t DrawLineAlgorithms::bresenham_float(const QLine &line, Drawer &drawer, bool display, bool steps)
{
    int ax = line.p1().x(), ay = line.p1().y();
    int bx = line.p2().x(), by = line.p2().y();

    int dx = bx - ax, dy = by - ay;
    int xsign = sign(dx), ysign = sign(dy);

    dx = std::abs(dx), dy = std::abs(dy);

    int change = 0;
    if (dy >= dx)
    {
        std::swap(dx, dy);
        change = 1;
    }

    double m = (double)dy / dx;
    double e = m - 0.5;

    int x = ax, y = ay;
    int x_buf = x, y_buf = y;
    int32_t step = 1;

    for (int i = 0; i <= dx; i++)
    {
        if (display)
            drawer.drawPoint(x, y);

        if (e >= 0)
        {
            if (1 == change)
                x += xsign;
            else
                y += ysign;
            e--;
        }
        if (e <= 0)
        {
            if (1 == change)
                y += ysign;
            else
                x += xsign;
            e += m;
        }

        if (!steps)
            continue;

        if (x_buf != x && y_buf != y)
            step++;

        x_buf = x;
        y_buf = y;
    }

    return step;
}

int32_t DrawLineAlgorithms::bresenham_antialised(const QLine &line, Drawer &drawer, bool display, bool steps)
{
    int ax = line.p1().x(), ay = line.p1().y();
    int bx = line.p2().x(), by = line.p2().y();

    int dx = bx - ax, dy = by - ay;
    int xsign = sign(dx), ysign = sign(dy);

    dx = std::abs(dx), dy = std::abs(dy);

    int change = 0;
    if (dy >= dx)
    {
        std::swap(dx, dy);
        change = 1;
    }

    double m = (double)dy / dx;
    double e = 0.5;

    int x = ax, y = ay;

    int colorAlpha = getColorALpha(e);
    if (display)
        drawer.drawPoint(x, y, colorAlpha);

    double W = 1 - m;
    int x_buf = x, y_buf = y;
    int32_t step = 1;

    for (int i = 0; i <= dx; i++)
    {
        if (e < W)
        {
            if (0 == change)
                x += xsign;
            else
                y += ysign;
            e += m;
        }
        else
        {
            x += xsign;
            y += ysign;
            e -= W;
        }

        int colorAlpha = getColorALpha(e);
        if (display)
            drawer.drawPoint(x, y, colorAlpha);

        if (!steps)
            continue;

        if (x_buf != x && y_buf != y)
            step++;

        x_buf = x;
        y_buf = y;
    }

    return step;
}
