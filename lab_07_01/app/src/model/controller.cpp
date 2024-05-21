#include "controller.h"
#include "simplelineclippingalgorithm.h"



Controller::Controller() : Controller(new QImage(600, 600, QImage::Format_RGB32))
{
}


Controller::Controller(QImage *image) : Controller(image, nullptr)
{
}

Controller::Controller(QImage *image, QStandardItemModel *linesTableModel) :
    _image(image),
    linesTable(linesTableModel)
{
    if (linesTable)
        linesTableInit();

    clearScreen();
}

Controller::~Controller()
{
    delete _image;
    delete linesTable;
}

void Controller::setLinesModel(QStandardItemModel *linesTableModel)
{
    delete linesTable;
    linesTable = linesTableModel;
    linesTableInit();
}


void Controller::setCutterRect(const QRect &rect)
{
    cutterRect = std::unique_ptr<QRect>(new QRect(rect.normalized()));

    redrawLines();

    Drawer drawer(_image, _cutterColor);
    drawer.drawRect(rect);

    emit imageChanged();
    emit cutterRectSetted(*cutterRect);
}

void Controller::resetCutterRect()
{
    cutterRect = nullptr;
    redrawLines();

    emit imageChanged();
}


void Controller::cutOff()
{
    if (!cutterRect)
        throw QString("Отсекатель не задан!\n");


    Drawer drawer(_image, _cutterColor);
    drawer.setBrushColor(Qt::white);
    drawer.drawRect(*cutterRect);

    drawer.setColor(_resColor);
    SimpleLineClippingAlgorithm::clipping(lines, *cutterRect, drawer);

    emit imageChanged();
}

void Controller::addLine(const QLine &line)
{
    Drawer drawer(_image, _lineColor);

    QString p1_label = QString::asprintf("(%d, %d)", line.p1().x(), line.p1().y());
    QString p2_label = QString::asprintf("(%d, %d)", line.p2().x(), line.p2().y());

    addRowToTable(p1_label, p2_label);

    lines.append(line);

    drawer.drawLine(line);
    emit imageChanged();
}

void Controller::removeLastLine()
{
    lines.removeLast();
    removeLastRowFormTable();

    redrawLines();
    emit imageChanged();
}



void Controller::clearScreen()
{
    _image->fill(Qt::white);
    lines.clear();
    resetCutterRect();
    clearLinesTable();

    emit imageChanged();
}


void Controller::linesTableInit()
{
    linesTable->setColumnCount(2);
    linesTable->setRowCount(0);

    linesTable->setHorizontalHeaderLabels({"Начало", "Конец"});
}

void Controller::removeLastRowFormTable()
{
    linesTable->removeRow(linesTable->rowCount()-1);
}

void Controller::addRowToTable(QString x, QString y)
{
    if (!linesTable)
        return;

    const QList<QStandardItem *> row = {new QStandardItem(x), new QStandardItem(y)};

    linesTable->appendRow(row);
}

void Controller::clearLinesTable()
{
    if (!linesTable)
        return;
    linesTable->removeRows(0, linesTable->rowCount());
}

void Controller::redrawLines()
{
    _image->fill(Qt::white);
    Drawer drawer(_image, _lineColor);
    for (const QLine &l : lines)
        drawer.drawLine(l);
}
