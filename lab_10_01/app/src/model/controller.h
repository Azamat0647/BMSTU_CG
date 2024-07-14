#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "drawer.h"
#include "polygon.h"
#include <QtWidgets>
#include <QMatrix4x4>

#include <stdexcept>

struct range_t
{
    qreal from;
    qreal to;
    qreal step;
};

using func_t = qreal (*)(qreal x, qreal z);

class Controller : public QObject
{
    Q_OBJECT
  public:
    explicit Controller(QImage *image);
    Controller();

    ~Controller();

    QImage *image()
    {
        return _image;
    };

    void rotateX(qreal angle);
    void rotateY(qreal angle);
    void rotateZ(qreal angle);

    void scale(qreal k);

    void draw(range_t xrange, range_t zrange, func_t func, const QColor &color);

    void clearScreen();

  signals:
    void imageChanged();

  private:
    QImage *_image;

    QMatrix4x4 matrix;

    void initMatrix();
};

#endif // CONTROLLER_H
