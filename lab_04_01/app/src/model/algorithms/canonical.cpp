#include "../drawcirclealgs.h"
#include "../drawellipsealgs.h"

void DrawCircleAlgs::canonical(const QPoint &center, int radius, Drawer &drawer)
{
    int r_p = radius * radius;
    for (unsigned int x = 0; x <= int(radius / std::sqrt(2)); ++x)
    {
        double y = sqrt(r_p - x * x);
        draw_1_8mirrored_points(x, y, center, drawer);
    }
}

void DrawEllipseAlgs::canonical(const QPoint &center, int ra, int rb, Drawer &drawer)
{
    double sqrA = ra * ra;
    double sqrB = rb * rb;

    int xRange = round(sqrA / sqrt(sqrA + sqrB));
    double sqrtCoef = rb / double(ra);

    int x = 0, y = 0;
    for (; x <= xRange; x++)
    {
        y = round(sqrtCoef * sqrt(sqrA - x * x));

        draw_1_4mirrored_points(x, y, center, drawer);
    }

    y = 0;
    int yRange = round(sqrB / sqrt(sqrA + sqrB));
    sqrtCoef = ra / double(rb);

    for (; y <= yRange; y++)
    {
        x = round(sqrtCoef * sqrt(sqrB - y * y));

        draw_1_4mirrored_points(x, y, center, drawer);
    }
}
