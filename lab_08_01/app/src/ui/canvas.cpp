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
        if (!_controller.pointsIsEmpty())
            _controller.removeLastCutterPoint();
        else
            _controller.removeLastLine();
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
        if (!_controller.pointsIsEmpty())
            return;

        QPoint p = event->scenePos().toPoint();
        if (!lineFirstPoint)
        {
            lineFirstPoint = std::unique_ptr<QPoint>(new QPoint(p));
        }
        else
        {
            if (straightLineMode)
                p = getStraightLinePoint(*lineFirstPoint, p);
            _controller.addLine(QLine(*lineFirstPoint, p));
            lineFirstPoint = nullptr;
        }
    }
    else if (event->button() == Qt::RightButton)
    {
        if (lineFirstPoint)
            return;

        QPoint p = event->scenePos().toPoint();

        if (straightLineMode)
            p = getStraightLinePoint(_controller.lastCutterPoint(), p);

        _controller.addCutterPoint(p);
    }
    else if (event->button() == Qt::MiddleButton)
    {
        _controller.closeCutterPolygon();
    }
}

void Canvas::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (!lineFirstPoint and _controller.pointsIsEmpty())
        return;

    QPixmap tmp_pixmap = QPixmap::fromImage(_image);
    QPainter p;
    QPoint mousePos(event->scenePos().toPoint());

    QPoint p2 = mousePos;

    p.begin(&tmp_pixmap);
    if (lineFirstPoint)
    {
        if (straightLineMode)
            p2 = getStraightLinePoint(*lineFirstPoint, mousePos);
        p.setPen(QPen(_controller.lineColor()));
        p.drawLine(*lineFirstPoint, p2);
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


