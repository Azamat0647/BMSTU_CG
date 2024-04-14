#include <gtest/gtest.h>
#include <QPoint>
#include "triangle.h"
#include <QtNumeric>


TEST(TriangleTest, InvalidTriangle)
{
    Triangle nullTr;

    EXPECT_FALSE(nullTr.isValid());
}

TEST(TriangleTest, ValidTriangle)
{
    Triangle validTr(QPointF(15, 70),
                     QPointF(50, 5),
                     QPointF(-30, -10));

    EXPECT_TRUE(validTr.isValid());

    QPointF orth = validTr.orthocenter();

    EXPECT_FLOAT_EQ(orth.x(), 24.49782);
    EXPECT_FLOAT_EQ(orth.y(), 19.34498);
}

TEST(TriangleTest, RightTriangle)
{
    Triangle rightTr(QPointF(25, 80),
                     QPointF(25, -30),
                     QPointF(-40, -30));

    EXPECT_TRUE(rightTr.isValid());

    QPointF orth = rightTr.orthocenter();

    EXPECT_FLOAT_EQ(orth.x(), 25.0);
    EXPECT_FLOAT_EQ(orth.y(), -30.0);
}
