#include "controller.h"
#include "cyrusbeckclippingalgorithm.h"



Controller::Controller() : Controller(new QImage(600, 600, QImage::Format_RGB32))
{
}


Controller::Controller(QImage *image) : Controller(image, nullptr, nullptr)
{
}

Controller::Controller(QImage *image,
                       QStandardItemModel *linesTableModel,
                       QStandardItemModel *cutterTableModel) :
    _image(image),
    linesTable(linesTableModel),
    cutterTable(cutterTableModel)
{
    if (linesTable)
        linesTableInit();
    if (cutterTable)
        cutterTableInit();

    clearScreen();
}

Controller::~Controller()
{
    delete _image;
    delete linesTable;
    delete cutterTable;
}

void Controller::setLinesModel(QStandardItemModel *linesTableModel)
{
    delete linesTable;
    linesTable = linesTableModel;
    linesTableInit();
}

void Controller::setCutterModel(QStandardItemModel *cutterTableModel)
{
    delete cutterTable;
    cutterTable = cutterTableModel;
    cutterTableInit();
}


void Controller::closeCutterPolygon()
{
    cutterPolygon = std::unique_ptr<Polygon>(new Polygon(cutterPoints));
    redrawLines();

    Drawer drawer(_image, _cutterColor);
    drawer.drawPolygon(*cutterPolygon);

    cutterPoints.clear();
    addRowToTable("End", "End", cutterTable);

    emit imageChanged();
    emit cutterSetted(*cutterPolygon);
}

void Controller::resetCutterPolygon()
{
    cutterPolygon = nullptr;
    redrawLines();

    emit imageChanged();
}


void Controller::cutOff()
{
    if (!cutterPolygon)
        throw QString("Отсекатель не задан!\n");


    Drawer drawer(_image, _cutterColor);
    drawer.setBrushColor(Qt::white);
    drawer.drawPolygon(*cutterPolygon);

    drawer.setColor(_resColor);

    QList<QLine> res = CyrusBeckClippingAlgorithm::cuttOff(lines.toList(),
                                                           *cutterPolygon);

    for (const QLine &l : res)
    {
        drawer.drawLine(l);
    }

    emit imageChanged();
}

void Controller::addLine(const QLine &line)
{
    Drawer drawer(_image, _lineColor);

    QString p1_label = QString::asprintf("(%d, %d)", line.p1().x(), line.p1().y());
    QString p2_label = QString::asprintf("(%d, %d)", line.p2().x(), line.p2().y());

    addRowToTable(p1_label, p2_label, linesTable);

    lines.append(line);

    drawer.drawLine(line);
    emit imageChanged();
}

void Controller::addCutterPoint(const QPoint &point)
{
    if (cutterPolygon)
    {
        redrawLines();
        resetCutterPolygon();
        clearTable(cutterTable);
    }

    Drawer drawer(_image, _cutterColor);
    if (cutterPoints.empty())
        drawer.drawPoint(point);
    else
    {
        drawer.drawLine(QLine(cutterPoints.last(), point));
    }

    cutterPoints.append(point);
    addRowToTable(QString::number(point.x()),
                  QString::number(point.y()),
                  cutterTable);

    emit imageChanged();
}

void Controller::removeLastLine()
{
    if (lines.isEmpty())
        return;

    lines.removeLast();

    removeLastRowFormTable(linesTable);

    redrawLines();

    Drawer drawer(_image, _cutterColor);
    if (cutterPolygon)
        drawer.drawPolygon(*cutterPolygon);
    else if (cutterPoints.size() > 1)
        drawer.drawPolyline(cutterPoints);

    emit imageChanged();
}

void Controller::removeLastCutterPoint()
{
    if (cutterPoints.empty())
        return;

    cutterPoints.removeLast();

    removeLastRowFormTable(cutterTable);

    redrawLines();

    Drawer drawer(_image, _cutterColor);
    drawer.drawPolyline(cutterPoints);

    emit imageChanged();
}

QPoint Controller::lastCutterPoint()
{
    return cutterPoints.last();
}



void Controller::clearScreen()
{
    _image->fill(Qt::white);

    lines.clear();
    cutterPoints.clear();

    resetCutterPolygon();

    clearTable(linesTable);
    clearTable(cutterTable);

    emit imageChanged();
}


void Controller::linesTableInit()
{
    linesTable->setColumnCount(2);
    linesTable->setRowCount(0);

    linesTable->setHorizontalHeaderLabels({"P1", "P2"});
}

void Controller::cutterTableInit()
{
    cutterTable->setColumnCount(2);
    cutterTable->setRowCount(0);

    cutterTable->setHorizontalHeaderLabels({"X", "Y"});
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

void Controller::redrawLines()
{
    _image->fill(Qt::white);
    Drawer drawer(_image, _lineColor);
    for (const QLine &l : lines)
        drawer.drawLine(l);
}
