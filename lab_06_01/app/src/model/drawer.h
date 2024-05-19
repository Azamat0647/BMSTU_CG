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

    QColor color() const
    {
        return _pen.color();
    };
    QColor pixelColor(int x, int y) const
    {
        return _image->pixelColor(x, y);
    }
    bool pixelOutOfRange(int x, int y) const
    {
        return (x > _image->width() - 1) or (x < 0) or (y > _image->height() - 1) or (y < 0);
    }

    void setPen(const QPen &pen);
    void setColor(const QColor &color);
    void setWidth(int width);

    void drawPoint(const QPoint &point)
    {
        p.drawPoint(point);
    };
    void drawPoint(int x, int y);
    void drawPoint(int x, int y, int color_alpha);

    void drawLine(const QLine &line);
    void drawLine(const QPoint &p1, const QPoint &p2)
    {
        p.drawLine(p1, p2);
    };
};

#endif // DRAWER_H
