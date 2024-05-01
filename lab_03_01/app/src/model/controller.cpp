#include "controller.h"

Controller::Controller() : Controller(new QImage(600, 600, QImage::Format_RGB32))
{
}

Controller::Controller(QImage *image) : _image(image)
{
    clearScreen();
}

Controller::~Controller()
{
    delete _image;
}

AlgFuncPtr Controller::getAlgFunc(int alg_type)
{
    AlgFuncPtr alg_func;

    switch (alg_type)
    {
    case BRESENHEM_INT:
        alg_func = DrawLineAlgorithms::bresenham_int;
        break;
    case BRESENHEM_FLOAT:
        alg_func = DrawLineAlgorithms::bresenham_float;
        break;
    case BRESENHEM_ANIT:
        alg_func = DrawLineAlgorithms::bresenham_antialised;
        break;
    case WU:
        alg_func = DrawLineAlgorithms::wu;
        break;
    case DDA:
        alg_func = DrawLineAlgorithms::dda;
        break;
    case STD:
        alg_func = DrawLineAlgorithms::std;
        break;
    default:
        alg_func = nullptr;
    }

    return alg_func;
}

void Controller::drawSpectrum(spectrum_t spectrum, int alg_type, const QColor &color)
{
    AlgFuncPtr alg_func = getAlgFunc(alg_type);
    Drawer drawer(_image, color, 1);

    QPoint center(_image->width() / 2, _image->height() / 2);
    for (int t = 0; t < 360; t += spectrum.step)
    {
        float rad = qDegreesToRadians(float(t));
        QPoint end(center.x() + spectrum.radius * qCos(rad), center.y() + spectrum.radius * qSin(rad));

        alg_func(QLine(center, end), drawer, true, false);
    }
}

void Controller::drawLine(const QLine &line, int alg_type, const QColor &color)
{
    AlgFuncPtr alg_func = getAlgFunc(alg_type);
    Drawer drawer(_image, color, 1);

    alg_func(line, drawer, true, false);
}

QList<qreal> Controller::algorithmsTimes(spectrum_t spectrum, int repeat_count)
{
    using std::chrono::duration;
    using std::chrono::duration_cast;
    using std::chrono::high_resolution_clock;
    using std::chrono::microseconds;

    Drawer drawer(_image);

    QPoint center(_image->width() / 2, _image->height() / 2);
    QList<qreal> times;

    for (int alg = 0; alg <= STD; alg++)
    {
        AlgFuncPtr alg_func = getAlgFunc(alg);
        double total = 0;
        for (int i = 0; i < repeat_count; i++)
            for (int t = 0; t < 360; t += spectrum.step)
            {
                float rad = qDegreesToRadians(float(t));
                QPoint p2(center.x() + spectrum.radius * qCos(rad), center.y() + spectrum.radius * qSin(rad));

                QLine line(center, p2);

                auto start = high_resolution_clock::now();
                alg_func(line, drawer, false, false);
                auto end = high_resolution_clock::now();

                total += (double)duration_cast<microseconds>(end - start).count();
            }

        times << total / repeat_count;
    }

    clearScreen();

    return times;
}

QList<QPointF> Controller::algorithmsStepsCount(spectrum_t spect, int alg_type)
{
    QList<QPointF> stepsList;
    AlgFuncPtr alg_func = getAlgFunc(alg_type);

    Drawer drawer(_image);

    QPoint center(_image->width() / 2, _image->height() / 2);
    for (int t = 0; t <= 90; t += spect.step)
    {
        float rad = qDegreesToRadians(float(t));

        QPoint p2(center.x() + spect.radius * qCos(rad), center.y() + spect.radius * qSin(rad));

        int steps = alg_func(QLine(center, p2), drawer, false, true);

        stepsList.append(QPoint(t, steps));
    }

    return stepsList;
}

void Controller::clearScreen()
{
    _image->fill(Qt::white);
}
