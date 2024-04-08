#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "cross.h"


class Ellipse : public Cross
{
private:
    float _startAngle, _endAngle;
public:
    Ellipse() = default;
    Ellipse(const QPointF &center, float a, float b,
            float startAngle=0, float endAngle=M_PI*2);
    void draw(QChart *chart, const QPen &pen);

};

#endif // ELLIPSE_H
