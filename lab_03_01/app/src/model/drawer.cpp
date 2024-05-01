#include "drawer.h"

Drawer::Drawer(QImage *image) : _image(image), _pen(QColor("black")), p(_image)
{
}

Drawer::Drawer(QImage *image, const QPen &pen) : _image(image), _pen(pen), p(_image)
{
}
Drawer::Drawer(QImage *image, const QColor &color, int width) : _image(image), _pen(QBrush(color), width), p(_image)
{
}

void Drawer::setPen(const QPen &pen)
{
    _pen = pen;
}

void Drawer::setColor(const QColor &color)
{
    _pen.setColor(color);
}

void Drawer::setWidth(int width)
{
    _pen.setWidth(width);
}

void Drawer::drawPoint(int x, int y)
{
    p.setPen(_pen);

    p.drawPoint(x, y);
}

void Drawer::drawPoint(int x, int y, int color_alpha)
{
    QColor color = _pen.color();

    color.setAlpha(color_alpha);

    p.setPen(QPen(color));

    p.drawPoint(x, y);
}

void Drawer::drawLine(const QLine &line)
{
    p.setPen(_pen);

    p.drawLine(line);
}
