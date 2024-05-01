#ifndef DRAWER_H
#define DRAWER_H

#include <QtWidgets>

class Drawer
{
  private:
    QImage *_image;
    QPen _pen;
    QPainter p;

  public:
    explicit Drawer(QImage *image);
    Drawer(QImage *image, const QPen &pen);
    Drawer(QImage *image, const QColor &color, int width);

    void setPen(const QPen &pen);
    void setColor(const QColor &color);
    void setWidth(int width);

    void drawPoint(int x, int y);
    void drawPoint(int x, int y, int color_alpha);

    void drawLine(const QLine &line);
};

#endif // DRAWER_H
