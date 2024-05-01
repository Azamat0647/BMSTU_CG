#include "../drawlinealgorithms.h"

int32_t DrawLineAlgorithms::dda(const QLine &line, Drawer &drawer, bool display, bool steps)
{
    int ax = line.p1().x(), ay = line.p1().y();
    int bx = line.p2().x(), by = line.p2().y();

    int dx = bx - ax, dy = by - ay;
    int l = std::max(std::abs(dx), std::abs(dy));

    double xsign = (double)dx / l, ysign = (double)dy / l;

    double x = ax, y = ay;
    double x_buf = x, y_buf = y;
    int step = 1;

    for (int i = 0; i < l; ++i)
    {
        if (display)
            drawer.drawPoint(std::round(x), std::round(y));

        x += xsign;
        y += ysign;

        if (!steps)
            continue;

        if (std::round(x_buf) != std::round(x) && std::round(y_buf) != std::round(y))
            step++;

        x_buf = x;
        y_buf = y;
    }

    return step;
}
