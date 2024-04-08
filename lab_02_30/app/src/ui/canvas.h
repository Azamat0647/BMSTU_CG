#ifndef CANVAS_H
#define CANVAS_H

#include <QtCharts>
#include "../model/figure.h"

class Canvas : public QChartView
{
public:
    Canvas(QWidget *parent = nullptr);
    void moveFigure(const QVector2D &move_vect);
    void rotateFigure(const QPointF &center, float angle);
    void scaleFigure(const QPointF &center, const QVector2D &scale_vect);

    void resetFigure();

private:
    Figure figure;
    Figure initialFigure;
    QVector2D axesRangeMin, axesRangeMax;
    void updateAxesSize();
    void updateScreen();
    void resizeEvent(QResizeEvent *event) override;
};

#endif // CANVAS_H
