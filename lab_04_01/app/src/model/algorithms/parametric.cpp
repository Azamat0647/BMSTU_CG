#include <cmath>

#include "../drawcirclealgs.h"
#include "../drawellipsealgs.h"

void DrawCircleAlgs::parametric(const QPoint &center, int radius, Drawer &drawer)
{
    double step = 1 / double(radius);
    int x, y;
    for (double t = 0; t <= M_PI_4; t += step)
    {
        x = radius * cos(t);
        y = radius * sin(t);

        draw_1_8mirrored_points(x, y, center, drawer);
    }
}

void DrawEllipseAlgs::parametric(const QPoint &center, int ra, int rb, Drawer &drawer)
{
    double step = 1 / double(ra > rb ? ra : rb);
    int x, y;

    for (double t = 0; t <= M_PI_2; t += step)
    {
        x = ra * cos(t);
        y = rb * sin(t);

        draw_1_4mirrored_points(x, y, center, drawer);
    }
}
