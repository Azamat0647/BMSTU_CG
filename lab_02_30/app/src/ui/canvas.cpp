#include "canvas.h"

Canvas::Canvas(QWidget *parent)
    : QChartView(parent), figure(QPoint(0, 0), 100, 34), axesRangeMin(-100, -100), axesRangeMax(100, 100)
{
    setbuf(stdout, NULL);
    initialFigure = figure;

    auto chart = new QChart;

    auto axisX = new QValueAxis;
    auto axisY = new QValueAxis;

    axisX->setRange(axesRangeMin.x(), axesRangeMax.x());
    axisY->setRange(axesRangeMin.y(), axesRangeMax.y());

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    chart->legend()->hide();

    setChart(chart);
    setRenderHint(QPainter::Antialiasing);

    updateScreen();
}

void Canvas::moveFigure(const QVector2D &move_vector)
{
    figure.move(move_vector);
    updateScreen();
}

void Canvas::rotateFigure(const QPointF &center, float angle)
{
    figure.rotate(center, angle);
    updateScreen();
}

void Canvas::scaleFigure(const QPointF &center, const QVector2D &scale_vector)
{
    figure.scale(center, scale_vector);
    updateScreen();
}

void Canvas::updateScreen()
{
    chart()->removeAllSeries();

    Drawer drawer(chart(), QColor("blue"), 2);

    figure.draw(drawer);
}

void Canvas::resetFigure()
{
    figure = initialFigure;
    updateScreen();
}

void Canvas::updateAxesSize()
{
    QChart *ch = chart();

    auto axisX = ch->axes(Qt::Horizontal).first();
    auto axisY = ch->axes(Qt::Vertical).first();

    float minX = axesRangeMin.x();
    float maxX = axesRangeMax.x();

    float minY = axesRangeMin.y();
    float maxY = axesRangeMax.y();

    float min = std::min(minX, minY);
    float max = std::max(maxX, maxY);

    float k = (float)height() / width();
    minX = min;
    maxX = max;
    minY = min;
    maxY = max;

    if (k < 1)
    {
        maxX = max + (max - min) * (1 / k - 1) / 2;
        minX = min - (max - min) * (1 / k - 1) / 2;
    }
    else if (k > 1)
    {
        maxY = max + (max - min) * (k - 1) / 2;
        minY = min - (max - min) * (k - 1) / 2;
    }

    axisX->setRange(minX, maxX);
    axisY->setRange(minY, maxY);
}

void Canvas::resizeEvent(QResizeEvent *event)
{
    QChartView::resizeEvent(event);
    updateAxesSize();
}
