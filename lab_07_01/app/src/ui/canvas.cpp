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
        if (rectFirstCorner)
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
        if (!rectFirstCorner)
        {
            rectFirstCorner = std::unique_ptr<QPoint>(new QPoint(p));
            _controller.resetCutterRect();
        }
        else
        {
            _controller.setCutterRect(QRect(*rectFirstCorner, p));
            rectFirstCorner = nullptr;
        }
    }
}

void Canvas::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (!lineFirstPoint and !rectFirstCorner)
        return;

    QPixmap tmp_pixmap = QPixmap::fromImage(_image);
    QPainter p;
    QPoint mousePos(event->scenePos().toPoint());

    if (lineFirstPoint)
    {
        QPoint p2 = mousePos;
        if (straightLineMode)
            p2 = getStraightLinePoint(*lineFirstPoint, mousePos);
        p.begin(&tmp_pixmap);
        p.setPen(QPen(_controller.lineColor()));
        p.drawLine(*lineFirstPoint, p2);
        p.end();
    }
    else
    {
        p.begin(&tmp_pixmap);
        p.setPen(QPen(_controller.cutterColor()));
        p.drawRect(QRect(*rectFirstCorner, mousePos));
        p.end();
    }

    pixmap_item->setPixmap(tmp_pixmap);
}


