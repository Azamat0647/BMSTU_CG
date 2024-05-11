#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QtWidgets>

#include "drawcirclealgs.h"
#include "drawellipsealgs.h"

enum algorithm_type_t
{
    BRESENHAM,
    CANONICAL,
    PARAMETRIC,
    MID_POINT,
    STD
};

struct circle_t
{
    int radius;
    QPoint center;
};

struct ellipse_t
{
    int ra;
    int rb;
    QPoint center;
};

struct circle_spectrum_t
{
    int Rbegin;
    int step;
    int count;
};

struct ellipse_spectrum_t
{
    int RaBegin;
    int RbBegin;
    int step;
    bool stepByRb = false;
    int count;
};

using CircleAlgFuncPtr_t = void (*)(const QPoint &, int, Drawer &);
using EllipseAlgFuncPtr_t = void (*)(const QPoint &, int, int, Drawer &);

class Controller
{
  public:
    Controller();
    explicit Controller(QImage *image);

    ~Controller();

    QImage *image()
    {
        return _image;
    };

    void drawCircleSpectrum(circle_spectrum_t spectrum, int alg_type, const QColor &color);
    void drawEllipseSpectrum(ellipse_spectrum_t spectrum, int alg_type, const QColor &color);

    void drawCircle(circle_t circle, int alg_type, const QColor &color);
    void drawEllipse(ellipse_t ellipse, int alg_type, const QColor &color);

    QList<QPointF> circleAlgorithmTimes(int alg_type);
    QList<QPointF> ellipseAlgorithmTimes(int alg_type);

    void clearScreen();

  private:
    QImage *_image;

    CircleAlgFuncPtr_t getCircleAlgFunc(int alg_type);
    EllipseAlgFuncPtr_t getEllipseAlgFunc(int alg_type);
};

#endif // CONTROLLER_H
