#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "drawlinealgorithms.h"
#include <QtWidgets>

enum algorithm_type_t
{
    DDA,
    BRESENHEM_INT,
    BRESENHEM_FLOAT,
    BRESENHEM_ANIT,
    WU,
    STD
};

struct spectrum_t
{
    int radius;
    int step;
};

using AlgFuncPtr = int (*)(const QLine &, Drawer &, bool, bool);

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

    void drawSpectrum(spectrum_t spectrum, int alg_type, const QColor &color);

    void drawLine(const QLine &line, int alg_type, const QColor &color);

    QList<qreal> algorithmsTimes(spectrum_t spectrum, int repeat_count);

    QList<QPointF> algorithmsStepsCount(spectrum_t spect, int alg_type);
    void clearScreen();

  private:
    QImage *_image;

    AlgFuncPtr getAlgFunc(int alg_type);
};

#endif // CONTROLLER_H
