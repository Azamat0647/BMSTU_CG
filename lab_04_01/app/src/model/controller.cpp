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

CircleAlgFuncPtr_t Controller::getCircleAlgFunc(int alg_type)
{
    CircleAlgFuncPtr_t alg_func;

    switch (alg_type)
    {
    case BRESENHAM:
        alg_func = DrawCircleAlgs::bresenham;
        break;
    case CANONICAL:
        alg_func = DrawCircleAlgs::canonical;
        break;
    case PARAMETRIC:
        alg_func = DrawCircleAlgs::parametric;
        break;
    case MID_POINT:
        alg_func = DrawCircleAlgs::midpoint;
        break;
    case STD:
        alg_func = DrawCircleAlgs::std;
        break;
    default:
        alg_func = nullptr;
    }

    return alg_func;
}

EllipseAlgFuncPtr_t Controller::getEllipseAlgFunc(int alg_type)
{
    EllipseAlgFuncPtr_t alg_func;

    switch (alg_type)
    {
    case BRESENHAM:
        alg_func = DrawEllipseAlgs::bresenham;
        break;
    case CANONICAL:
        alg_func = DrawEllipseAlgs::canonical;
        break;
    case PARAMETRIC:
        alg_func = DrawEllipseAlgs::parametric;
        break;
    case MID_POINT:
        alg_func = DrawEllipseAlgs::midpoint;
        break;
    case STD:
        alg_func = DrawEllipseAlgs::std;
        break;
    default:
        alg_func = nullptr;
    }

    return alg_func;
}

void Controller::drawCircle(circle_t circle, int alg_type, const QColor &color)
{
    CircleAlgFuncPtr_t draw_circle_func = getCircleAlgFunc(alg_type);

    Drawer drawer(_image, color, 1);

    draw_circle_func(circle.center, circle.radius, drawer);
}

void Controller::drawEllipse(ellipse_t ellipse, int alg_type, const QColor &color)
{
    EllipseAlgFuncPtr_t draw_ellipse_func = getEllipseAlgFunc(alg_type);

    Drawer drawer(_image, color, 1);

    draw_ellipse_func(ellipse.center, ellipse.ra, ellipse.rb, drawer);
}

void Controller::drawCircleSpectrum(circle_spectrum_t spectrum, int alg_type, const QColor &color)
{
    CircleAlgFuncPtr_t draw_circle_func = getCircleAlgFunc(alg_type);
    Drawer drawer(_image, color, 1);

    QPoint center(_image->width() / 2, _image->height() / 2);

    int r = spectrum.Rbegin;
    for (int i = 0; i < spectrum.count; i++)
    {
        draw_circle_func(center, r, drawer);
        r += spectrum.step;
    }
}

void Controller::drawEllipseSpectrum(ellipse_spectrum_t spectrum, int alg_type, const QColor &color)
{
    EllipseAlgFuncPtr_t draw_ellipse_func = getEllipseAlgFunc(alg_type);
    Drawer drawer(_image, color, 1);

    QPoint center(_image->width() / 2, _image->height() / 2);

    int ra = spectrum.RaBegin;
    int rb = spectrum.RbBegin;

    double coef = (spectrum.stepByRb) ? (double(ra) / rb) : (double(rb) / ra);

    for (int i = 0; i < spectrum.count; i++)
    {
        draw_ellipse_func(center, ra, rb, drawer);

        if (spectrum.stepByRb)
        {
            rb += spectrum.step;
            ra = std::ceil(rb * coef);
        }
        else
        {
            ra += spectrum.step;
            rb = std::ceil(ra * coef);
        }
    }
}

QList<QPointF> Controller::circleAlgorithmTimes(int alg_type)
{
    using std::chrono::duration;
    using std::chrono::duration_cast;
    using std::chrono::high_resolution_clock;
    using std::chrono::microseconds;

    int repeat_count = 50;

    Drawer drawer(_image);
    QPoint center(_image->width() / 2, _image->height() / 2);

    CircleAlgFuncPtr_t draw_circle_func = getCircleAlgFunc(alg_type);
    QList<QPointF> times;

    times << QPointF(0, 0);

    double total;
    for (int r = 20; r <= 1000; r += 20)
    {
        total = 0;
        for (int i = 0; i < repeat_count; i++)
        {
            auto start = high_resolution_clock::now();
            draw_circle_func(center, r, drawer);
            auto end = high_resolution_clock::now();

            total += (double)duration_cast<microseconds>(end - start).count();
        }
        times << QPointF(r, total / repeat_count);
    }

    return times;
}

QList<QPointF> Controller::ellipseAlgorithmTimes(int alg_type)
{
    using std::chrono::duration;
    using std::chrono::duration_cast;
    using std::chrono::high_resolution_clock;
    using std::chrono::microseconds;

    int repeat_count = 50;

    Drawer drawer(_image);
    QPoint center(_image->width() / 2, _image->height() / 2);

    EllipseAlgFuncPtr_t draw_ellipse_func = getEllipseAlgFunc(alg_type);
    QList<QPointF> times;

    times << QPointF(0, 0);
    float coef = 1 / 2.0;
    for (int ra = 20; ra <= 1000; ra += 20)
    {
        int rb = ra * coef;
        auto start = high_resolution_clock::now();
        for (int i = 0; i < repeat_count; i++)
        {
            draw_ellipse_func(center, ra, rb, drawer);
        }
        auto end = high_resolution_clock::now();
        times << QPointF(ra, (double)duration_cast<microseconds>(end - start).count());
    }

    return times;
}

void Controller::clearScreen()
{
    _image->fill(Qt::white);
}
