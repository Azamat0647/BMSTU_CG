#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

class Canvas : public QGraphicsScene
{
  public:
    Canvas(QImage &image, QObject *parent = nullptr);

  public slots:
    void updateScene();

  private:
    QImage &_image;
    QGraphicsPixmapItem *pixmap_item;
};

#endif // CANVAS_H
