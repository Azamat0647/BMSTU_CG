#include "controller.h"
#include "floodfillalgorithm.h"

Controller::Controller() : Controller(new QImage(600, 600, QImage::Format_RGB32))
{
}

Controller::Controller(QImage *image) : Controller(image, nullptr)
{
}

Controller::Controller(QImage *image, QStandardItemModel *pointsTableModel)
    : _image(image), pointsTable(pointsTableModel)
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

void Controller::setSeedPoint(const QPoint &point)
{
    seedPoint = std::unique_ptr<QPoint>(new QPoint(point));
    emit seedPointChanged(*seedPoint);
}

void Controller::resetSeedPoint()
{
    seedPoint = nullptr;
}

void Controller::fill(const QColor &color, unsigned int delay)
{
    if (!seedPoint)
        throw QString("Затравочная точка не задана!");

    if (!points.isEmpty())
        throw QString("закраска невозможна, так как имеется незамкнутый полигон\n");

    Drawer drawer(_image, color, 1);

    FloodFillAlgorithm filler(drawer);

    connect(&filler, SIGNAL(screenUpdated()), this, SIGNAL(imageChanged()));

    filler.fill(*seedPoint, delay);

    emit imageChanged();
}

void Controller::addPoint(const QPoint &point)
{
    Drawer drawer(_image);

    addRowToTable(QString::number(point.x()), QString::number(point.y()));
    if (points.isEmpty())
    {
        points.append(point);
        drawer.drawPoint(point);
        emit imageChanged();
        return;
    }
    const QPoint &last = points.last();
    points.append(point);

    drawer.drawLine(QLine(last, point));
    emit imageChanged();
}

void Controller::closePolygon()
{
    if (points.size() < 3)
        return;

    Drawer drawer(_image);

    drawer.drawLine(points.first(), points.last());

    points.clear();

    addRowToTable("end", "end");

    emit imageChanged();
}

QPoint Controller::lastPoint()
{
    return points.last();
}

void Controller::removeLastPoint()
{
    if (points.isEmpty())
        return;

    QPoint last = points.last();
    points.removeLast();
    removeLastRowFormTable();

    if (!points.isEmpty())
    {
        Drawer drawer(_image, QColor(Qt::white), 1);
        drawer.drawLine(points.last(), last);
    }

    emit imageChanged();
}

void Controller::clearScreen()
{
    _image->fill(Qt::white);
    points.clear();
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
    pointsTable->removeRow(pointsTable->rowCount() - 1);
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
