#include "controller.h"

Controller::Controller() :
    Controller(new QChartView)
{

}

Controller::Controller(QChartView *view)
    : _view(view), _chart(new QChart), figure(QPoint(0, 0), 100, 34)
{
    initialFigure = figure;

    chartInit();
}

Controller::~Controller()
{
    delete _view;
}

void Controller::chartInit()
{
    auto axisX = new QValueAxis;
    auto axisY = new QValueAxis;

    axisX->setRange(-100, 100);
    axisY->setRange(-100, 100);

    _chart->addAxis(axisX, Qt::AlignBottom);
    _chart->addAxis(axisY, Qt::AlignLeft);

    _chart->legend()->hide();

    _view->setChart(_chart);
    _view->setRenderHint(QPainter::Antialiasing);

    updateScreen();
}

void Controller::setView(QChartView *view)
{
    delete _view;

    _view = view;
    _chart = new QChart;

    chartInit();
}

void Controller::moveFigure(const QVector2D &move_vector)
{
    figure.move(move_vector);
    updateScreen();
}

void Controller::rotateFigure(const QPointF &center, float angle)
{
    figure.rotate(center, angle);
    updateScreen();
}

void Controller::scaleFigure(const QPointF &center, const QVector2D &scale_vector)
{
    figure.scale(center, scale_vector);
    updateScreen();
}

void Controller::updateScreen()
{
    _chart->removeAllSeries();

    Drawer drawer(_chart, QColor("blue"), 2);

    figure.draw(drawer);
}

void Controller::resetFigure()
{
    figure = initialFigure;
    updateScreen();
}

