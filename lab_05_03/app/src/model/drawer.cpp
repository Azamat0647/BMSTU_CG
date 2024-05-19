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
    p.drawPoint(x, y);
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

void Drawer::invertPixel(int x, int y)
{
    if (_image->pixelColor(x, y) == backgroundColor)
        _image->setPixelColor(x, y, _pen.color());
    else if (_image->pixelColor(x, y) == _pen.color())
        _image->setPixelColor(x, y, backgroundColor);
}
