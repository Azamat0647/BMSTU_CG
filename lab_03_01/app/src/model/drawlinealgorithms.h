#ifndef DRAWLINEALGORITHMS_H
#define DRAWLINEALGORITHMS_H

#include "drawer.h"

class DrawLineAlgorithms
{
  public:
    static int32_t bresenham_int(const QLine &line, Drawer &drawer, bool display = true, bool steps = false);

    static int32_t bresenham_float(const QLine &line, Drawer &drawer, bool display = true, bool steps = false);

    static int32_t bresenham_antialised(const QLine &line, Drawer &drawer, bool display = true, bool steps = false);

    static int32_t dda(const QLine &line, Drawer &drawer, bool display = true, bool steps = false);

    static int32_t wu(const QLine &line, Drawer &drawer, bool display = true, bool steps = false);

    static int32_t std(const QLine &line, Drawer &drawer, bool display = true, bool steps = false)
    {
        drawer.drawLine(line);

        return 0;
    };

  private:
    static int getColorALpha(double e)
    {
        return std::clamp(int(e * 255), 0, 255);
    };

    static inline int sign(double x)
    {
        if (x < 0)
            return -1;

        if (x > 0)
            return 1;

        return 0;
    }
};

#endif // DRAWLINEALGORITHMS_H
