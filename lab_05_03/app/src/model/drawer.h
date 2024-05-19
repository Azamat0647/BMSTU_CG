#ifndef DRAWER_H
#define DRAWER_H

#include <QtWidgets>

class Drawer
{
  private:
    QImage *_image;
    QPen _pen;
    QColor backgroundColor{Qt::white};
    QPainter p;

  public:
    explicit Drawer(QImage *image);
    Drawer(QImage *image, const QPen &pen);
    Drawer(QImage *image, const QColor &color, int width);

    void setPen(const QPen &pen);
    void setColor(const QColor &color);
    void setWidth(int width);


    void drawPoint(const QPoint &point) { p.drawPoint(point); };
    void drawPoint(int x, int y);
    void drawPoint(int x, int y, int color_alpha);

    void drawLine(const QLine &line);
    void drawLine(const QPoint &p1, const QPoint &p2) { p.drawLine(p1, p2); };

    void invertPixel(int x, int y);
};

#endif // DRAWER_H
