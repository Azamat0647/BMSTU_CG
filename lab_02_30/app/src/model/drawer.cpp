#include "drawer.h"

void Drawer::addSeriesToChart(QLineSeries *series)
{
    auto axisX = chart->axes(Qt::Horizontal).first();
    auto axisY = chart->axes(Qt::Vertical).first();

    chart->addSeries(series);

    series->attachAxis(axisX);
    series->attachAxis(axisY);
}

void Drawer::addPointsToSeries(const QList<Point2D> &points, QLineSeries *series)
{
    printf("addPointstoser size: %d\n", points.size());
    for (int i = 0; i < points.size(); i++)
    {
        series->append(points[i]);
    }
}

void Drawer::drawLine(const QPointF &p1, const QPointF &p2)
{
    auto line = new QLineSeries();

    line->setPen(pen);

    line->append(p1);
    line->append(p2);

    addSeriesToChart(line);

    printf("draw line\n");
}

void Drawer::drawPolygon(const QList<Point2D> &points)
{
    auto series = new QLineSeries();

    series->setPen(pen);

    addPointsToSeries(points, series);
    series->append(points.first());

    addSeriesToChart(series);
    printf("draw polygon\n");
}

void Drawer::drawPolyline(const QList<Point2D> &points)
{
    auto series = new QLineSeries();

    series->setPen(pen);

    addPointsToSeries(points, series);

    addSeriesToChart(series);
    printf("draw polyline\n");
}
