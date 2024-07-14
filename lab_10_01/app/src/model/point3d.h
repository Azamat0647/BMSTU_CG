#ifndef POINT3D_H
#define POINT3D_H

#include <QtGlobal>
#include <QMatrix4x4>


class Point3D
{
public:
    Point3D();
    Point3D(const QPoint &p);
    Point3D(qreal x, qreal y, qreal z);

    inline qreal x() const { return _x; };
    inline qreal y() const { return _y; };
    inline qreal z() const { return _z; };

    inline QPoint toQPoint() const { return QPoint(_x, _y); };
    bool operator==(const Point3D &p) const
    {
        return qFuzzyCompare(_x, p.x()) and
                qFuzzyCompare(_y, p.y()) and
                qFuzzyCompare(_z, p.z());
    };


    void transform(const QMatrix4x4 &matrix);

private:
    qreal _x;
    qreal _y;
    qreal _z;
};


#endif // POINT3D_H
