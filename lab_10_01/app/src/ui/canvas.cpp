#include "canvas.h"

Canvas::Canvas(QImage &image, QObject *parent) :
    QGraphicsScene(parent),
    _image(image)
{
    pixmap_item = addPixmap(QPixmap::fromImage(_image));

}

void Canvas::updateScene()
{
    pixmap_item->setPixmap(QPixmap::fromImage(_image));
}



