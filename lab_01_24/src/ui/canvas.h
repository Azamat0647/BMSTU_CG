#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsView>
#include "../model/setofpoints.h"
#include "../model/triangle.h"



class Canvas: public QWidget
{
    Q_OBJECT

    SetOfPoints *points;
    Triangle *foundTriangle;
    bool show_triangle;
    QRectF sceneRect;

public:
    Canvas(QWidget *parent = nullptr);
    ~Canvas();
    SetOfPoints* getPoints();
    void find_triangle();
    void clear_triangle();
    void update_display();
    void clear();

    //void update();

private:
    void triangle_not_found_message();

    void paintEvent(QPaintEvent *event) override;
    void update_scene_rect();

    QPoint point_transform_to_display(QPointF point);
    void draw_points(QPainter &painter);
    void draw_point(QPointF point, QColor color, QPainter &painter);
    void draw_triangle(QPainter &painter);
    void draw_coord_axes(QPainter &painter);
    QRect get_axes_range();


};

#endif // CANVAS_H
