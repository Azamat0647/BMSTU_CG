#include "ellipse.h"

Ellipse::Ellipse(const QPointF &center, float a, float b, float startAngle, float endAngle)
    : Shape(center), _startAngle(startAngle), _endAngle(endAngle)
{
    basePoints.append(Point2D(center.x() + a, center.y()));
    basePoints.append(Point2D(center.x(), center.y() + b));
}

void Ellipse::draw(Drawer &drawer)
{
    int n = 100;

    n *= (_endAngle - _startAngle) / (2 * M_PI);

    Point2D a = basePoints[0];
    Point2D b = basePoints[1];

    printf("a: (%.2f, %.2f)\n", a.x(), a.y());
    printf("b: (%.2f, %.2f)\n", b.x(), b.y());

    QList<Point2D> points;

    for (int i = 0; i < n; i++)
    {
        float t = _startAngle + i * (_endAngle - _startAngle) / (n - 1);

        float x = (_center.x() + (a.x() - _center.x()) * qCos(t) + (b.x() - _center.x()) * qSin(t));

        float y = (_center.y() + (a.y() - _center.y()) * qCos(t) + (b.y() - _center.y()) * qSin(t));

        points.append(Point2D(x, y));
    }

    drawer.drawPolyline(points);
}
