#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QPoint>
#include <QRect>
#include <cmath>

class Triangle {

private:
  QPointF _orthocenter;

  QPointF _A;
  QPointF _B;
  QPointF _C;

  QPointF calculate_orthocenter();

public:
  Triangle(QPointF A, QPointF B, QPointF C);

  bool isValid();
  QPointF orthocenter();
  QRectF BoundingRect();

  QPointF A();
  QPointF B();
  QPointF C();
};

#endif // TRIANGLE_H
