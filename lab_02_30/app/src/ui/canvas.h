#ifndef CANVAS_H
#define CANVAS_H

#include <QtCharts>

class Canvas : public QChartView
{
  public:
    using QChartView::QChartView;

  private:
    QVector2D axesRangeMin{-100, -100}, axesRangeMax{100, 100};

    void updateAxesSize();
    void resizeEvent(QResizeEvent *event) override;
};

#endif // CANVAS_H
