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
        if (!_controller.cutterPointsIsEmpty())
            _controller.removeLastCutterPoint();
        else if (!_controller.polygonPointsIsEmpty())
            _controller.removeLastPolygonPoint();
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
        if (!_controller.cutterPointsIsEmpty())
            return;

        QPoint p = event->scenePos().toPoint();

        if (straightLineMode and !_controller.polygonPointsIsEmpty())
            p = getStraightLinePoint(_controller.lastPolygonPoint(), p);

        _controller.addPolygonPoint(p);
    }
    else if (event->button() == Qt::RightButton)
    {
        if (!_controller.polygonPointsIsEmpty())
            return;

        QPoint p = event->scenePos().toPoint();

        if (straightLineMode and !_controller.cutterPointsIsEmpty())
            p = getStraightLinePoint(_controller.lastCutterPoint(), p);

        _controller.addCutterPoint(p);
    }
    else if (event->button() == Qt::MiddleButton)
    {
        if (!_controller.cutterPointsIsEmpty())
            _controller.closeCutter();
        else if (!_controller.polygonPointsIsEmpty())
            _controller.closePolygon();
    }
}

void Canvas::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (_controller.polygonPointsIsEmpty() and
            _controller.cutterPointsIsEmpty())
        return;

    QPixmap tmp_pixmap = QPixmap::fromImage(_image);
    QPainter p;
    QPoint mousePos(event->scenePos().toPoint());

    QPoint p2 = mousePos;

    p.begin(&tmp_pixmap);
    if (!_controller.polygonPointsIsEmpty())
    {
        QPoint p1 = _controller.lastPolygonPoint();
        if (straightLineMode)
            p2 = getStraightLinePoint(p1, mousePos);

        p.setPen(QPen(_controller.polygonColor()));
        p.drawLine(p1, p2);

        pixmap_item->setPixmap(tmp_pixmap);
    }
    else
    {
        QPoint p1 = _controller.lastCutterPoint();
        if (straightLineMode)
            p2 = getStraightLinePoint(p1, mousePos);

        p.setPen(QPen(_controller.cutterColor()));
        p.drawLine(p1, p2);

        pixmap_item->setPixmap(tmp_pixmap);
    }
    p.end();

    pixmap_item->setPixmap(tmp_pixmap);
}


