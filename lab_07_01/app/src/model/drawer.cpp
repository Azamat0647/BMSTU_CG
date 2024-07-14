#include "drawer.h"


Drawer::Drawer(QImage *image, const QPen &pen) : _image(image), _pen(pen), p(_image)
{
    p.setPen(_pen);
}

Drawer::Drawer(QImage *image) : Drawer(image, QPen(QColor("black")))
{
}


Drawer::Drawer(QImage *image, const QColor &color, int width) : Drawer(image, QPen(QBrush(color), width))
{
}

void Drawer::setPen(const QPen &pen)
{
    _pen = pen;
    p.setPen(_pen);
}

void Drawer::setColor(const QColor &color)
{
    _pen.setColor(color);
    p.setPen(_pen);
}

void Drawer::setBrushColor(const QColor &color)
{
    p.setBrush(QBrush(color));
}

void Drawer::setWidth(int width)
{
    _pen.setWidth(width);
    p.setPen(_pen);
}

void Drawer::drawPoint(int x, int y)
{
    p.drawPoint(x, y);
}

void Drawer::drawRect(const QRect &rect)
{
    p.drawRect(rect);
}

void Drawer::drawPoint(int x, int y, int color_alpha)
{
    QColor color = _pen.color();

    color.setAlpha(color_alpha);

    _pen.setColor(color);

    p.drawPoint(x, y);
}

void Drawer::drawLine(const QLine &line)
{
    p.drawLine(line);
}
