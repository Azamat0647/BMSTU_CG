#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "figure.h"
#include <QtCharts>

class Controller
{
  public:
    Controller();
    Controller(QChartView *view);
    ~Controller();

    void setView(QChartView *view);

    void moveFigure(const QVector2D &move_vect);
    void rotateFigure(const QPointF &center, float angle);
    void scaleFigure(const QPointF &center, const QVector2D &scale_vect);

    void resetFigure();

  private:
    Figure figure;
    Figure initialFigure;
    QChart *_chart;
    QChartView *_view;

    void chartInit();
    void updateScreen();
};

#endif // CONTROLLER_H
