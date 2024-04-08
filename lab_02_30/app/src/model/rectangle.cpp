#include "rectangle.h"

Rectangle::Rectangle(const QPointF &center, float width, float height) :
    _topLeft(center.x() - width/2, center.y() - height/2),
    _bottomRight(center.x() + width/2, center.y() + height/2),
    _topRight(center.x() + width/2, center.y() - height/2),
    _bottomLeft(center.x() - width/2, center.y() + height/2)
{

}

void Rectangle::move(const QVector2D &move_vect)
{
    _topLeft.move(move_vect);
    _topRight.move(move_vect);
    _bottomLeft.move(move_vect);
    _bottomRight.move(move_vect);
}

void Rectangle::rotate(const QPointF &center, float angle)
{
    _topLeft.rotate(center, angle);
    _topRight.rotate(center, angle);
    _bottomLeft.rotate(center, angle);
    _bottomRight.rotate(center, angle);
}

void Rectangle::scale(const QPointF &center, const QVector2D &scale_vect)
{
    _topLeft.scale(center, scale_vect);
    _topRight.scale(center, scale_vect);
    _bottomLeft.scale(center, scale_vect);
    _bottomRight.scale(center, scale_vect);
}

void Rectangle::draw(QChart *chart, const QPen &pen)
{

    auto series = new QLineSeries();

    series->setPen(pen);

    auto axisX = chart->axes(Qt::Horizontal).first();
    auto axisY = chart->axes(Qt::Vertical).first();

    series->append(_topLeft);
    series->append(_topRight);
    series->append(_bottomRight);
    series->append(_bottomLeft);
    series->append(_topLeft);

    chart->addSeries(series);

    series->attachAxis(axisX);
    series->attachAxis(axisY);

}

