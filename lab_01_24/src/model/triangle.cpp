#include "triangle.h"
#include <QVector2D>


Triangle::Triangle(QPointF A, QPointF B, QPointF C): _A(A), _B(B), _C(C)
{
    _orthocenter = calculate_orthocenter();
}

QPointF Triangle::calculate_orthocenter()
{
    if (!isValid())
        return QPoint();

    QPointF n1(_A - _B);
    QPointF n2(_A - _C);

    float x, y;

    if ((n1.y() == 0) and (n2.y() == 0))
    {
        return _A;
    }
    else if (n1.y() == 0)
    {
        x = n1.x();
        y = (QPointF::dotProduct(n2, _B) - x*n2.x())/n2.y();
    }
    else if (n2.y() == 0)
    {
        x = n1.x();
        y = (QPointF::dotProduct(n1, _C) - x*n1.x())/n1.y();
    }
    else
    {
        float d = n1.x()/n1.y() - n2.x()/n2.y();

        x = QPointF::dotProduct(n1, _C)/(n1.y()*d)
            - QPointF::dotProduct(n2, _B)/(n2.y()*d);

        y = (QPointF::dotProduct(n1, _C) - x*n1.x())/n1.y();
    }

    return QPointF(x, y);
}

bool Triangle::isValid()
{
    return !(QVector2D(_A - _B) * QVector2D(_A -_C)).isNull();
}

QPointF Triangle::orthocenter()
{
    return _orthocenter;
}

QRectF Triangle::BoundingRect()
{
    float top, bottom, left, right;

    top = std::max({_A.y(), _B.y(), _C.y(), _orthocenter.y()});
    right = std::max({_A.x(), _B.x(), _C.x(), _orthocenter.x()});
    bottom = std::min({_A.y(), _B.y(), _C.y(), _orthocenter.y()});
    left = std::min({_A.x(), _B.x(), _C.x(), _orthocenter.x()});

    return QRectF(QPointF(left, top), QPointF(right, bottom));
}


QPointF Triangle::A()
{
    return _A;
}

QPointF Triangle::B()
{
    return _B;
}

QPointF Triangle::C()
{
    return _C;
}
