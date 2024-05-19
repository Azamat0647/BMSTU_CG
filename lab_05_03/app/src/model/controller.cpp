#include "controller.h"

Controller::Controller() : Controller(new QImage(600, 600, QImage::Format_RGB32))
{
}


Controller::Controller(QImage *image) : Controller(image, nullptr)
{
}

Controller::Controller(QImage *image, QStandardItemModel *pointsTableModel) :
    _image(image),
    pointsTable(pointsTableModel)
{
    if (pointsTable)
        pointsTableInit();

    clearScreen();
}

Controller::~Controller()
{
    delete _image;
    delete pointsTable;
}

void Controller::setPointsModel(QStandardItemModel *pointsTableModel)
{
    delete pointsTable;
    pointsTable = pointsTableModel;
    pointsTableInit();
}

void Controller::fillLine(const QPoint &inters_point, int partition, Drawer &drawer, int delay)
{
    if (inters_point.x() < partition)
        for (int x = inters_point.x() + 1; x < partition; x++)
            drawer.invertPixel(x, inters_point.y());
    else
        for (int x = inters_point.x(); x >= partition; x--)
            drawer.invertPixel(x, inters_point.y());

    if (delay)
    {
        emit imageChanged();
        QTime sleepTime = QTime::currentTime().addMSecs(delay);
        while (QTime::currentTime() < sleepTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, delay);
    }
}

void Controller::fill(const QColor &color, unsigned int delay)
{
    Drawer drawer(_image, color, 1);
    int x_partition;

    for (Polygon &pol : polygons)
    {
        x_partition = 0;
        for (QPoint &p : pol)
            x_partition += p.x();
        x_partition /= pol.size();

        QList<QLine> edges = pol.edges();
        for (QLine &edge : edges)
        {
            QPoint p1 = edge.p1(), p2 = edge.p2();

            if (p1.y() > p2.y())
                std::swap(p1, p2);

            int dx = p2.x() - p1.x(), dy = p2.y() - p1.y();

            double step = double(dx) / dy;
            double x = p1.x();
            for (int y = p1.y(); y < p2.y(); y += 1)
            {
                fillLine(QPoint(x, y), x_partition, drawer, delay);
                x += step;
            }
        }
    }

    emit imageChanged();
}

void Controller::addPoint(const QPoint &point)
{
    Drawer drawer(_image);

    addRowToTable(QString::number(point.x()), QString::number(point.y()));
    if (curPolygon.isEmpty())
    {
        curPolygon.append(point);
        drawer.drawPoint(point);
        emit imageChanged();
        return;
    }
    const QPoint &last = curPolygon.last();
    curPolygon.append(point);

    drawer.drawLine(QLine(last, point));
    emit imageChanged();
}

void Controller::closePolygon()
{
    if (curPolygon.size() < 3)
        return;

    Drawer drawer(_image);

    drawer.drawLine(curPolygon.first(), curPolygon.last());

    polygons.append(curPolygon);
    curPolygon.clear();

    addRowToTable("end", "end");

    emit imageChanged();
}

QPoint Controller::lastPoint()
{
    return curPolygon.last();
}

void Controller::removeLastPoint()
{
    if (curPolygon.isEmpty())
        return;

    QPoint last = curPolygon.last();
    curPolygon.removeLast();
    removeLastRowFormTable();

    if (!curPolygon.isEmpty())
    {
        Drawer drawer(_image, QColor(Qt::white), 1);
        drawer.drawLine(curPolygon.last(), last);
    }

    emit imageChanged();
}


void Controller::clearScreen()
{
    _image->fill(Qt::white);
    curPolygon.clear();
    polygons.clear();
    clearPointsTable();

    emit imageChanged();
}


void Controller::pointsTableInit()
{
    pointsTable->setColumnCount(2);
    pointsTable->setRowCount(0);

    pointsTable->setHorizontalHeaderLabels({"X", "Y"});
}

void Controller::removeLastRowFormTable()
{
    pointsTable->removeRow(pointsTable->rowCount()-1);
}

void Controller::addRowToTable(QString x, QString y)
{
    if (!pointsTable)
        return;

    const QList<QStandardItem *> row = {new QStandardItem(x), new QStandardItem(y)};

    pointsTable->appendRow(row);
}

void Controller::clearPointsTable()
{
    if (!pointsTable)
        return;
    pointsTable->removeRows(0, pointsTable->rowCount());
}
