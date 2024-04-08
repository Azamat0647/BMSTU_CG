#include "figure.h"
#include "ellipse.h"
#include "rhombus.h"
#include "rectangle.h"


Figure::Figure(const QPointF &center, float width, float height) :
    bodyRect(center, width - height, height),
    rhombus(center, width - height, height),
    centerCross(center, height/2, height/2),
    centerCircle(center, height/4, height/4),
    rightArc(QPoint(center.x() + width/2 - height/2, center.y()),
            height/2, height/2, -M_PI_2, M_PI_2),
    leftArc(QPoint(center.x() - width/2 + height/2, center.y()),
            height/2, height/2, M_PI_2, 3*M_PI_2)
{

}

void Figure::move(const QVector2D &move_vect)
{
    bodyRect.move(move_vect);
    rhombus.move(move_vect);
    centerCircle.move(move_vect);
    centerCross.move(move_vect);
    rightArc.move(move_vect);
    leftArc.move(move_vect);
}

void Figure::rotate(const QPointF &center, float angle)
{
    bodyRect.rotate(center, angle);
    rhombus.rotate(center, angle);
    centerCircle.rotate(center, angle);
    centerCross.rotate(center, angle);
    rightArc.rotate(center, angle);
    leftArc.rotate(center, angle);
}

void Figure::scale(const QPointF &center, const QVector2D &scale_vect)
{
    bodyRect.scale(center, scale_vect);
    rhombus.scale(center, scale_vect);
    centerCircle.scale(center, scale_vect);
    centerCross.scale(center, scale_vect);
    rightArc.scale(center, scale_vect);
    leftArc.scale(center, scale_vect);
}

void Figure::draw(QChart *chart)
{
    QPen pen(QColor("blue"));
    pen.setWidth(2);

    bodyRect.draw(chart, pen);
    rhombus.draw(chart, pen);
    centerCircle.draw(chart, pen);
    centerCross.draw(chart, pen);
    rightArc.draw(chart, pen);
    leftArc.draw(chart, pen);
}
