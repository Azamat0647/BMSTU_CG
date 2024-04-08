#include "rhombus.h"


void Rhombus::draw(QChart *chart, const QPen &pen)
{
    auto series = new QLineSeries();

    series->setPen(pen);

    auto axisX = chart->axes(Qt::Horizontal).first();
    auto axisY = chart->axes(Qt::Vertical).first();

    series->append(_b);
    series->append(_a);
    series->append(_center - (_b - _center));
    series->append(_center - (_a - _center));
    series->append(_b);

    chart->addSeries(series);

    series->attachAxis(axisX);
    series->attachAxis(axisY);
}
