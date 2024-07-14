#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneEvent>

#include "../model/controller.h"

class Canvas : public QGraphicsScene
{
  public:
    Canvas(Controller &controller, QObject *parent = nullptr);

  public slots:
    void updateScene();

  protected:
    void keyPressEvent(QKeyEvent *keyEvent) override;
    void keyReleaseEvent(QKeyEvent *keyEvent) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

  private:
    Controller &_controller;
    QImage &_image;
    QGraphicsPixmapItem *pixmap_item;
    bool straightLineMode{false};

    inline QPoint getStraightLinePoint(const QPoint &p1, const QPoint &p2);
};

#endif // CANVAS_H
