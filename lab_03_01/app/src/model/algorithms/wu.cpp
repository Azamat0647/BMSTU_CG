#include "../drawlinealgorithms.h"

#include <cinttypes>
#include <cmath>

#include <QDebug>

int32_t DrawLineAlgorithms::wu(const QLine &line, Drawer &drawer, bool display, bool steps)
{
    int ax = line.p1().x(), ay = line.p1().y();
    int bx = line.p2().x(), by = line.p2().y();

    auto fpart = [](double x) -> double { return x - int(x); };
    auto ipart = [=](double x) -> double { return x - fpart(x); };
    auto rfpart = [=](double x) -> double { return 1 - fpart(x); };
    auto round = [=](double x) -> double { return ipart(x + 0.5); };

    const bool steep = std::abs(by - ay) > std::abs(bx - ax);
    if (steep)
    {
        std::swap(ax, ay);
        std::swap(bx, by);
    }
    if (ax > bx)
    {
        std::swap(ax, bx);
        std::swap(ay, by);
    }

    const int dx = bx - ax;
    const int dy = by - ay;
    const double gradient = (dx == 0) ? 1 : (double)dy / dx;

    int xpx11;
    double intery;
    {
        const double xend = round(ax);
        const double yend = ay + gradient * (xend - ax);
        const double xgap = rfpart(ax + 0.5);

        xpx11 = int(xend);
        const int ypx11 = ipart(yend);

        int color1Alpha = getColorALpha(rfpart(yend) * xgap);
        int color2Alpha = getColorALpha(fpart(yend) * xgap);
        if (display)
        {
            if (steep)
            {
                drawer.drawPoint(ypx11, xpx11, color1Alpha);
                drawer.drawPoint(ypx11 + 1, xpx11, color2Alpha);
            }
            else
            {
                drawer.drawPoint(xpx11, ypx11, color1Alpha);
                drawer.drawPoint(xpx11, ypx11 + 1, color2Alpha);
            }
        }

        intery = yend + gradient;
    }

    int xpx12;
    {
        const double xend = std::round(bx);
        const double yend = by + gradient * (xend - bx);
        const double xgap = rfpart(bx + 0.5);

        xpx12 = int(xend);
        const int ypx12 = ipart(yend);

        int color1Alpha = getColorALpha(rfpart(yend) * xgap);
        int color2Alpha = getColorALpha(fpart(yend) * xgap);
        if (display)
        {
            if (steep)
            {
                drawer.drawPoint(ypx12, xpx12, color1Alpha);
                drawer.drawPoint(ypx12 + 1, xpx12, color2Alpha);
            }
            else
            {
                drawer.drawPoint(xpx12, ypx12, color1Alpha);
                drawer.drawPoint(xpx12, ypx12 + 1, color2Alpha);
            }
        }
    }

    auto step = 0;

    for (int x = xpx11 + 1; x < xpx12; x++)
    {
        int color1Alpha = getColorALpha(rfpart(intery));
        int color2Alpha = getColorALpha(fpart(intery));
        if (display)
        {
            if (steep)
            {
                drawer.drawPoint(ipart(intery), x, color1Alpha);
                drawer.drawPoint(ipart(intery) + 1, x, color2Alpha);
            }
            else
            {
                drawer.drawPoint(x, ipart(intery), color1Alpha);
                drawer.drawPoint(x, ipart(intery) + 1, color2Alpha);
            }
        }

        if (steps && x < xpx12)
        {
            if (ipart(intery) != ipart(intery + gradient))
                ++step;
        }

        intery += gradient;
    }

    return step;
}
