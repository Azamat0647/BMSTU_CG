#include "canvas.h"

#include <QMessageBox>

Canvas::Canvas(QWidget *parent) : QWidget(parent)

{
    setbuf(stdout, NULL);

    points = new SetOfPoints();
    foundTriangle = nullptr;
    show_triangle = false;

    setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
}

Canvas::~Canvas()
{
    delete points;
    clear_triangle();
}

void Canvas::update_display()
{
    clear_triangle();
    update();
}

void Canvas::triangle_not_found_message()
{
    QMessageBox msgBox;
    msgBox.setText("с данным множеством точек невозможно построить ни один треугольник!");
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.exec();
}

void Canvas::find_triangle()
{
    clear_triangle();

    Triangle *max_triangle = nullptr;
    float max_summ = 0;
    for (int i = 0; i < points->lenght() - 2; i++)
        for (int j = i + 1; j < points->lenght() - 1; j++)
            for (int k = j + 1; k < points->lenght(); k++)
            {
                Triangle *triangle = new Triangle((*points)[i], (*points)[j], (*points)[k]);

                if (!triangle->isValid())
                {
                    delete triangle;
                    continue;
                }
                QPointF orth = triangle->orthocenter();

                if (orth.manhattanLength() > max_summ)
                {
                    max_summ = orth.manhattanLength();
                    max_triangle = triangle;
                    continue;
                }

                delete triangle;
            }

    if (!max_triangle)
    {
        triangle_not_found_message();
        return;
    }

    foundTriangle = max_triangle;

    show_triangle = true;
    update();
}

void Canvas::clear()
{
    points->clear_points();
    clear_triangle();
    update();
}

void Canvas::clear_triangle()
{
    if (foundTriangle)
        delete foundTriangle;

    foundTriangle = nullptr;
    show_triangle = false;
}

void Canvas::draw_triangle(QPainter &painter)
{
    if (!foundTriangle)
        return;

    QPen pen(QColor("gray"));
    pen.setWidth(3);
    painter.setPen(pen);

    QPointF A, B, C, o;

    A = point_transform_to_display(foundTriangle->A());
    B = point_transform_to_display(foundTriangle->B());
    C = point_transform_to_display(foundTriangle->C());

    o = point_transform_to_display(foundTriangle->orthocenter());

    painter.drawLine(A, o);
    painter.drawLine(B, o);
    painter.drawLine(C, o);

    pen.setColor("red");
    painter.setPen(pen);

    painter.drawLine(A, B);
    painter.drawLine(B, C);
    painter.drawLine(C, A);

    QPointF orth = foundTriangle->orthocenter();
    draw_point(foundTriangle->orthocenter(), QColor("blue"), painter);
    printf("orthocenter: (%.4f, %.4f)\n", orth.x(), orth.y());
}

void Canvas::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter p;
    //    QPen pen = QPen(QColor("black"));
    //    QBrush brush = QBrush(QColor("yellow"));

    p.begin(this);

    p.setRenderHint(QPainter::Antialiasing);
    p.setBackground(QBrush(QColor("white")));

    update_scene_rect();

    if (show_triangle)
        draw_triangle(p);

    draw_coord_axes(p);
    draw_points(p);

    p.end();
}

void Canvas::update_scene_rect()
{
    sceneRect.setRect(-50, 50, 100, -100);

    float top, bottom, left, right;

    if (show_triangle)
        sceneRect = foundTriangle->BoundingRect();
    else
    {
        sceneRect.setTop(std::max(sceneRect.top(), points->boundingRect().top()));
        sceneRect.setRight(std::max(sceneRect.right(), points->boundingRect().right()));
        sceneRect.setBottom(std::min(sceneRect.bottom(), points->boundingRect().bottom()));
        sceneRect.setLeft(std::min(sceneRect.left(), points->boundingRect().left()));
    }

    float size = std::max(sceneRect.width(), -sceneRect.height());
    sceneRect.setSize(QSizeF(size, -size));

    float m_h = sceneRect.width() / 10;
    float m_v = sceneRect.height() / 10;

    sceneRect += QMarginsF(m_h, m_v, m_h, m_v);

    float axes_size = sceneRect.width();

    float x_coeff = width() / axes_size;
    float y_coeff = height() / axes_size;

    if (width() / (float)height() > 1)
    {
        float new_width = width() / y_coeff;

        sceneRect.setLeft(sceneRect.left() - (new_width - axes_size) / 2);
        sceneRect.setRight(sceneRect.right() + (new_width - axes_size) / 2);
    }
    else if (width() / (float)height() < 1)
    {
        float new_height = height() / x_coeff;
        sceneRect.setBottom(sceneRect.bottom() - (new_height - axes_size) / 2);
        sceneRect.setTop(sceneRect.top() + (new_height - axes_size) / 2);
    }
}

SetOfPoints *Canvas::getPoints()
{
    return points;
}

void Canvas::draw_coord_axes(QPainter &painter)
{
    QPen pen = QPen(QColor("black"));

    painter.setPen(pen);

    QPointF zero_point = point_transform_to_display(QPointF(0, 0));

    if ((sceneRect.bottom() < 0) and (sceneRect.top() > 0))
        painter.drawLine(QLine(QPoint(30, zero_point.y()), QPoint(width(), zero_point.y())));

    if ((sceneRect.left() < 0) and (sceneRect.right() > 0))
        painter.drawLine(QLine(QPoint(zero_point.x(), 0), QPoint(zero_point.x(), height() - 20)));

    QPoint p;

    painter.drawLine(QPoint(30, height() - 20), QPoint(width(), height() - 20));
    painter.drawLine(QPoint(30, height() - 20), QPoint(30, 0));

    int n = (int)round(log10(sceneRect.width()));
    float step = pow(10, n - 1);

    QString draw_text;

    for (float xi = ((int)(sceneRect.left() / step)) * step; xi < sceneRect.right(); xi += step)
    {
        p = point_transform_to_display(QPointF(xi, 0));
        painter.drawLine(QPoint(p.x(), height() - 17), QPoint(p.x(), height() - 20));
        draw_text.setNum(xi);

        painter.drawText(p.x() - 10, height(), QString().setNum(xi));
    }

    for (float yi = ((int)(sceneRect.bottom() / step)) * step; yi < sceneRect.top(); yi += step)
    {
        p = point_transform_to_display(QPointF(0, yi));
        painter.drawLine(QPoint(27, p.y()), QPoint(30, p.y()));
        draw_text.setNum(yi);

        painter.drawText(0, p.y() + 5, QString().setNum(yi));
    }
}

QPoint Canvas::point_transform_to_display(QPointF point)
{
    float x_coeff = (width() - 30) / sceneRect.width();
    float y_coeff = (height() + 20) / sceneRect.height();

    int x, y;

    x = (int)((point.x() - sceneRect.left()) * x_coeff);
    y = (int)((point.y() - sceneRect.bottom()) * y_coeff + height());

    return QPoint(x + 30, y - 20);
}

void Canvas::draw_points(QPainter &painter)
{
    for (int i = 0; i < points->lenght(); i++)
    {
        draw_point((*points)[i], QColor("yellow"), painter);
    }
}

void Canvas::draw_point(QPointF point, QColor color, QPainter &painter)
{
    int radius = 5;
    QPen pen = QPen(QColor("black"));
    QBrush brush = QBrush(color);

    painter.setPen(pen);
    painter.setBrush(brush);

    QPointF p = point_transform_to_display(point);

    painter.drawEllipse(p, radius, radius);
}
