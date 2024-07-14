#include "canvas.h"


void Canvas::updateAxesSize()
{
    QChart *ch = chart();

    if (ch->axes(Qt::Horizontal).empty())
        return;

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
