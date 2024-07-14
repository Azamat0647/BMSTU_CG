#include "canvas.h"

Canvas::Canvas(Controller &controller, QObject *parent) :
    QGraphicsScene(parent),
    _controller(controller),
    _image(*controller.image())
{
    pixmap_item = addPixmap(QPixmap::fromImage(_image));

}

void Canvas::updateScene()
{
    pixmap_item->setPixmap(QPixmap::fromImage(_image));
}

QPoint Canvas::getStraightLinePoint(const QPoint &p1, const QPoint &p2)
{
    QPoint p = p2;

    int dx = abs(p2.x() - p1.x());
    int dy = abs(p2.y() - p1.y());

    if (dx > dy)
        p.setY(p1.y());
    else
        p.setX(p1.x());

    return p;
}

void Canvas::keyPressEvent(QKeyEvent *keyEvent)
{
    if (keyEvent->key() == Qt::Key_Control)
    {
        straightLineMode = true;
    }
    else if (keyEvent->key() == Qt::Key_Backspace)
    {
        _controller.removeLastPoint();
    }
}

void Canvas::keyReleaseEvent(QKeyEvent *keyEvent)
{
    if (keyEvent->key() == Qt::Key_Control)
    {
        straightLineMode = false;
    }
}

void Canvas::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        QPoint p(event->scenePos().x(), event->scenePos().y());

        if (straightLineMode)
            p = getStraightLinePoint(_controller.lastPoint(), p);

        _controller.addPoint(p);
    }
    else if (event->button() == Qt::RightButton)
    {
        _controller.closePolygon();
    }
}

void Canvas::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (_controller.pointsIsEmpty())
        return;

    QPoint p1 = _controller.lastPoint();
    QPoint mousePos(event->scenePos().toPoint());

    QPoint p2 = mousePos;

    if (straightLineMode)
        p2 = getStraightLinePoint(p1, mousePos);

    QPixmap tmp_pixmap = QPixmap::fromImage(_image);
    QPainter p;

    p.begin(&tmp_pixmap);
    p.drawLine(p1, p2);
    p.end();

    pixmap_item->setPixmap(tmp_pixmap);
}


