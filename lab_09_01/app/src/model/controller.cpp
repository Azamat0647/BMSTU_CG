#include "controller.h"
#include "sutherlandhodgmanalgorithm.h"


Controller::Controller() : Controller(new QImage(600, 600, QImage::Format_RGB32))
{
}


Controller::Controller(QImage *image) : Controller(image, nullptr, nullptr)
{
}

Controller::Controller(QImage *image,
                       QStandardItemModel *polygonTableModel,
                       QStandardItemModel *cutterTableModel) :
    _image(image),
    polygonTable(polygonTableModel),
    cutterTable(cutterTableModel)
{
    if (polygonTable)
        initTable(polygonTable);
    if (cutterTable)
        initTable(cutterTable);

    clearScreen();
}

Controller::~Controller()
{
    delete _image;
    delete polygonTable;
    delete cutterTable;
}

void Controller::setPolygonModel(QStandardItemModel *polygonTableModel)
{
    delete polygonTable;
    polygonTable = polygonTableModel;
    initTable(polygonTable);
}

void Controller::setCutterModel(QStandardItemModel *cutterTableModel)
{
    delete cutterTable;
    cutterTable = cutterTableModel;
    initTable(cutterTable);
}


void Controller::closeCutter()
{
    if (cutterPoints.size() < 3)
        return;

    cutter.reset(new Polygon(cutterPoints));

    Drawer drawer(_image, _cutterColor);
    drawer.drawLine(QLine(cutterPoints.last(), cutterPoints.first()));

    cutterPoints.clear();
    addRowToTable("End", "End", cutterTable);

    emit imageChanged();
}

void Controller::resetCutter()
{
    cutter.reset();

    redrawPolygons();
    clearTable(cutterTable);

    emit imageChanged();
}

void Controller::closePolygon()
{
    if (polygonPoints.size() < 3)
        return;


    polygons << Polygon(polygonPoints);

    Drawer drawer(_image, _polygonColor);
    drawer.drawLine(QLine(polygonPoints.last(), polygonPoints.first()));

    polygonPoints.clear();
    addRowToTable("End", "End", polygonTable);

    emit imageChanged();
}


void Controller::cutOff()
{
    if (!cutter)
        throw QString("Отсекатель не задан!\n");


    Drawer drawer(_image, _cutterColor);
    drawer.drawPolygon(*cutter);

    drawer.setColor(_resColor);
    drawer.setWidth(2);

    QList<Polygon> res = SutherlandHodgmanAlgorithm::cutOff(polygons, *cutter);

    for (const Polygon &p : res)
    {
        drawer.drawPolygon(p);
    }

    emit imageChanged();
}


void Controller::addCutterPoint(const QPoint &point)
{
    if (cutter)
        resetCutter();

    Drawer drawer(_image, _cutterColor);
    if (cutterPoints.empty())
        drawer.drawPoint(point);
    else
        drawer.drawLine(QLine(cutterPoints.last(), point));

    cutterPoints.append(point);
    addRowToTable(QString::number(point.x()),
                  QString::number(point.y()),
                  cutterTable);

    emit imageChanged();
}

void Controller::addPolygonPoint(const QPoint &point)
{
    Drawer drawer(_image, _polygonColor);
    if (polygonPoints.empty())
        drawer.drawPoint(point);
    else
        drawer.drawLine(QLine(polygonPoints.last(), point));

    polygonPoints.append(point);
    addRowToTable(QString::number(point.x()),
                  QString::number(point.y()),
                  polygonTable);

    emit imageChanged();
}


void Controller::removeLastCutterPoint()
{
    if (cutterPoints.empty())
        return;

    cutterPoints.removeLast();

    removeLastRowFormTable(cutterTable);

    redrawPolygons();

    Drawer drawer(_image, _cutterColor);
    drawer.drawPolyline(cutterPoints);

    emit imageChanged();
}

void Controller::removeLastPolygonPoint()
{
    if (polygonPoints.empty())
        return;

    polygonPoints.removeLast();

    removeLastRowFormTable(polygonTable);

    redrawPolygons();

    Drawer drawer(_image, _cutterColor);
    if (cutter)
        drawer.drawPolygon(*cutter);

    drawer.setColor(_polygonColor);
    drawer.drawPolyline(polygonPoints);

    emit imageChanged();
}


void Controller::clearScreen()
{
    _image->fill(Qt::white);

    cutterPoints.clear();
    polygonPoints.clear();

    cutter.reset();
    polygons.clear();

    clearTable(polygonTable);
    clearTable(cutterTable);

    emit imageChanged();
}



void Controller::initTable(QStandardItemModel *model)
{
    model->setColumnCount(2);
    model->setRowCount(0);

    model->setHorizontalHeaderLabels({"X", "Y"});
}

void Controller::removeLastRowFormTable(QStandardItemModel *model)
{
    model->removeRow(model->rowCount()-1);
}

void Controller::addRowToTable(QString x, QString y,
                               QStandardItemModel *model)
{
    if (!model)
        return;

    const QList<QStandardItem *> row = {new QStandardItem(x), new QStandardItem(y)};

    model->appendRow(row);
}

void Controller::clearTable(QStandardItemModel *model)
{
    if (!model)
        return;
    model->removeRows(0, model->rowCount());
}

void Controller::redrawPolygons()
{
    _image->fill(Qt::white);
    Drawer drawer(_image, _polygonColor);

    for (Polygon &polygon : polygons)
        drawer.drawPolygon(polygon);

}
