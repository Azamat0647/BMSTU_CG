#include "controller.h"
#include "floatinghorizonalgorithm.h"
#include <QtMath>


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

void Controller::rotateX(qreal angle)
{
    QMatrix4x4 m;

    angle = qDegreesToRadians(angle);

    qreal cos_a = qCos(angle);
    qreal sin_a = qSin(angle);

    m.fill(0);

    m(0, 0) = 1;

    m(1, 1) = cos_a;
    m(1, 2) = -sin_a;
    m(2, 1) = sin_a;
    m(2, 2) = cos_a;
    m(3, 3) = 1;

    matrix = m*matrix;
}

void Controller::rotateY(qreal angle)
{
    QMatrix4x4 m;

    angle = qDegreesToRadians(angle);

    qreal cos_a = qCos(angle);
    qreal sin_a = qSin(angle);

    m.fill(0);

    m(0, 0) = cos_a;
    m(0, 2) = sin_a;
    m(1, 1) = 1;
    m(2, 0) = -sin_a;
    m(2, 2) = cos_a;
    m(3, 3) = 1;

    matrix = m*matrix;
}

void Controller::rotateZ(qreal angle)
{
    QMatrix4x4 m;

    angle = qDegreesToRadians(angle);

    qreal cos_a = qCos(angle);
    qreal sin_a = qSin(angle);

    m.fill(0);

    m(0, 0) = cos_a;
    m(0, 1) = -sin_a;
    m(1, 0) = sin_a;
    m(1, 1) = cos_a;
    m(2, 2) = 1;
    m(3, 3) = 1;

    matrix = m*matrix;
}

void Controller::scale(qreal k)
{
    QMatrix4x4 m;
    m.fill(0);

    m(0, 0) = k;
    m(1, 1) = k;
    m(2, 2) = k;
    m(3, 3) = 1;

    matrix = m*matrix;
    matrix(3, 0) = _image->width()/2;
    matrix(3, 1) = _image->height()/2;
}

void Controller::draw(range_t xrange, range_t zrange, func_t func, const QColor &color)
{
    _image->fill(Qt::white);
    Drawer drawer(_image, color);

    FloatingHorizonAlgorithm::draw(func, xrange, zrange, matrix, drawer);

    emit imageChanged();
}


void Controller::clearScreen()
{
    _image->fill(Qt::white);

    initMatrix();

    emit imageChanged();
}

void Controller::initMatrix()
{
    matrix.fill(0);
    matrix(0, 0) = 1;
    matrix(1, 1) = 1;
    matrix(2, 2) = 1;
    matrix(3, 3) = 1;
    scale(30);
}


