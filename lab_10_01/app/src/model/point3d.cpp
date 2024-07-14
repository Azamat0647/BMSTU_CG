#include "point3d.h"

Point3D::Point3D() : Point3D(0, 0, 0)
{

}

Point3D::Point3D(const QPoint &p) : Point3D(p.x(), p.y(), 0)
{

}

Point3D::Point3D(qreal x, qreal y, qreal z) :
    _x(x), _y(y), _z(z)
{

}

void Point3D::transform(const QMatrix4x4 &matrix)
{
//    printf("\ntransform");
    QVector4D pointVect(_x, _y, _z, 1);
    QVector4D v(0, 0, 0, 0);

//    printf("\nv before: %.1f, %.1f, %.1f\nmatrix:\n\n", v.x(), v.y(), v.z());

//    for (int i = 0; i < 4; i++)
//    {
//        for (int j = 0; j < 4; j++)
//            printf("%.1f ", matrix(i, j));
//        printf("\n");
//    }

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            v[i] += pointVect[j] * matrix(j, i);

//    printf("\nv after: %.1f, %.1f, %.1f\n\n", v.x(), v.y(), v.z());

    _x = v.x();
    _y = v.y();
    _z = v.z();
}
