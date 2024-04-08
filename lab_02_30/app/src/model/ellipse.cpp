#include "ellipse.h"

Ellipse::Ellipse(const QPointF &center, float a, float b,
                 float startAngle, float endAngle) :
    Cross(center, a*2, b*2),
    _startAngle(startAngle),
    _endAngle(endAngle)
{

}

void Ellipse::draw(QChart *chart, const QPen &pen)
{
    int n = 100;

    n *= (_endAngle - _startAngle) / (2 * M_PI);

    auto series = new QLineSeries;

    series->setPen(pen);

    for (int i = 0; i < n; i++)
    {
        float t = _startAngle + i * (_endAngle - _startAngle) / (n-1);

        float x = (_center.x() + (_a.x() - _center.x()) * qCos(t) +
                      (_b.x() - _center.x()) * qSin(t));

        float y = (_center.y() + (_a.y() - _center.y()) * qCos(t) +
                      (_b.y() - _center.y()) * qSin(t));

        series->append(QPointF(x, y));
    }

    auto axisX = chart->axes(Qt::Horizontal).first();
    auto axisY = chart->axes(Qt::Vertical).first();

    chart->addSeries(series);

    series->attachAxis(axisX);
    series->attachAxis(axisY);
}
