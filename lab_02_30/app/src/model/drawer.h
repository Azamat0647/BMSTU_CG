#ifndef DRAWER_H
#define DRAWER_H

#include "point2d.h"
#include <QtCharts>

class Drawer
{
  private:
    QChart *chart;
    QPen pen;

    void addSeriesToChart(QLineSeries *series);
    void addPointsToSeries(const QList<Point2D> &points, QLineSeries *series);

  public:
    Drawer(QChart *chart) : chart(chart){};
    Drawer(QChart *chart, const QPen &pen) : chart(chart), pen(pen){};
    Drawer(QChart *chart, const QColor &color, int width) : chart(chart), pen(QBrush(color), width){};

    void drawPolygon(const QList<Point2D> &points);
    void drawPolyline(const QList<Point2D> &points);
    //    void drawLine(const QLineF &line);
    void drawLine(const QPointF &p1, const QPointF &p2);
};

#endif // DRAWER_H
