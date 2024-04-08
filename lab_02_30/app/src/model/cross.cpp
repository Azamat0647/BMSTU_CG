#include "cross.h"

Cross::Cross(const QPointF &center, float width, float height) :
    _center(center),
    _a(center.x() + width/2, center.y()),
    _b(center.x(), center.y() - height/2)
{

}

void Cross::move(const QVector2D &move_vect)
{
    _a.move(move_vect);
    _b.move(move_vect);
    _center.move(move_vect);
}

void Cross::rotate(const QPointF &center, float angle)
{
    _a.rotate(center, angle);
    _b.rotate(center, angle);
    _center.rotate(center, angle);
}

void Cross::scale(const QPointF &center, const QVector2D &scale_vect)
{
    _a.scale(center, scale_vect);
    _b.scale(center, scale_vect);
    _center.scale(center, scale_vect);
}


void Cross::draw(QChart *chart, const QPen &pen)
{
    auto line1 = new QLineSeries();
    auto line2 = new QLineSeries();

    line1->setPen(pen);
    line2->setPen(pen);

    auto axisX = chart->axes(Qt::Horizontal).first();
    auto axisY = chart->axes(Qt::Vertical).first();

    line1->append(_b);
    line1->append(_center - (_b - _center));

    line2->append(_a);
    line2->append(_center - (_a - _center));


    chart->addSeries(line1);
    chart->addSeries(line2);

    line1->attachAxis(axisX);
    line1->attachAxis(axisY);

    line2->attachAxis(axisX);
    line2->attachAxis(axisY);
}

