#include "floodfillalgorithm.h"

FloodFillAlgorithm::FloodFillAlgorithm(Drawer &drawer) : _drawer(drawer), _fillColor(drawer.color())
{
}

FloodFillAlgorithm::FloodFillAlgorithm(Drawer &drawer, const QColor &borderColor)
    : _drawer(drawer), _fillColor(drawer.color()), _borderColor(borderColor)
{
}

void FloodFillAlgorithm::findNewSeedPoints(int left, int right, int y, QStack<QPoint> &stack)
{
    int x = left;

    while (x <= right)
    {
        bool flag = false;

        while ((x < right) and !isBorder(x, y) and !isFilled(x, y))
        {
            flag = true;
            x++;
        }

        if (flag)
        {
            if ((x == right) and !isBorder(x, y) and !isFilled(x, y))
                stack.push(QPoint(x, y));
            else
                stack.push(QPoint(x - 1, y));
        }

        int tmpX = x;

        while ((isBorder(x, y) or isFilled(x, y)) and x < right)
            x++;

        if (x == tmpX)
            x++;
    }
}

void FloodFillAlgorithm::fill(const QPoint &seedPoint, unsigned int delay)
{
    QStack<QPoint> stack;

    stack.push(seedPoint);

    while (!stack.isEmpty())
    {
        QPoint curPoint = stack.pop();

        _drawer.drawPoint(curPoint);

        int x = curPoint.x() + 1;
        int y = curPoint.y();

        int left, right;

        while (!_drawer.pixelOutOfRange(x, y) and !isBorder(x, y))
        {
            _drawer.drawPoint(x, y);
            x++;
        }
        right = x - 1;

        x = curPoint.x() - 1;

        while (!_drawer.pixelOutOfRange(x, y) and !isBorder(x, y))
        {
            _drawer.drawPoint(x, y);
            x--;
        }
        left = x + 1;

        findNewSeedPoints(left, right, y + 1, stack);
        findNewSeedPoints(left, right, y - 1, stack);

        sleep(delay);
    }
}

void FloodFillAlgorithm::sleep(unsigned int delay)
{
    if (delay)
    {
        emit screenUpdated();
        QTime sleepTime = QTime::currentTime().addMSecs(delay);
        while (QTime::currentTime() < sleepTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, delay);
    }
}

bool FloodFillAlgorithm::isFilled(int x, int y)
{
    return _drawer.pixelColor(x, y) == _fillColor;
}

bool FloodFillAlgorithm::isBorder(int x, int y)
{
    return _drawer.pixelColor(x, y) == _borderColor;
}
