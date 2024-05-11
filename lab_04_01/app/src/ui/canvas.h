#ifndef CANVAS_H
#define CANVAS_H

#include <QtCharts>

class Canvas : public QChartView
{
  public:
    Canvas(QWidget *parent = nullptr);

  private:
    QVector2D axesRangeMin, axesRangeMax;

    void updateAxesSize();
    void resizeEvent(QResizeEvent *event) override;
};

#endif // CANVAS_H
