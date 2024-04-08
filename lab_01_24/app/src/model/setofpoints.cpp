#include "setofpoints.h"

SetOfPoints::SetOfPoints()
{
}

int SetOfPoints::lenght()
{
    return points.size();
}

void SetOfPoints::clear_points()
{
    points.clear();
    boundingRect_update();
}

int SetOfPoints::add_point(QPointF point)
{
    if (points.contains(point))
    {
        return ALREADY_EXIST_ERROR;
    }

    points.append(point);
    boundingRect_update();

    return OK;
}

int SetOfPoints::change_point(int index, QPointF new_point)
{
    if (points.contains(new_point))
    {
        return ALREADY_EXIST_ERROR;
    }

    points.replace(index, new_point);
    boundingRect_update();

    return OK;
}

void SetOfPoints::remove_point(int index)
{
    points.removeAt(index);
    boundingRect_update();
}

void SetOfPoints::boundingRect_update()
{
    _boundingRect.setRect(0, 0, 0, 0);

    for (QPointF p : points)
    {
        _boundingRect.setLeft(std::min(p.x(), _boundingRect.left()));
        _boundingRect.setRight(std::max(p.x(), _boundingRect.right()));
        _boundingRect.setBottom(std::min(p.y(), _boundingRect.bottom()));
        _boundingRect.setTop(std::max(p.y(), _boundingRect.top()));
    }
}

QRectF SetOfPoints::boundingRect()
{
    return _boundingRect;
}

QPointF &SetOfPoints::operator[](unsigned index)
{
    return points[index];
}
