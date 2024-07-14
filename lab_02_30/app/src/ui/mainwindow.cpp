#include "mainwindow.h"
#include "../model/figure.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    controller.setView(ui->graphicsView);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_aboutTaskAction_triggered()
{
    QString title = "Условие задачи, вариант 30";
    QString text = "Нарисовать исходный рисунок, осуществить его"
                   " перенос, масштабирование, поворот";
    QMessageBox::about(this, title, text);
}

void MainWindow::on_moveButton_clicked()
{
    float x = ui->moveX_spinBox->value();
    float y = ui->moveY_spinBox->value();

    QVector2D move_v(x, y);

    controller.moveFigure(move_v);
}

void MainWindow::on_rotateButton_clicked()
{
    float cx = ui->centerX_spinBox->value();
    float cy = ui->centerY_spinBox->value();

    float angle = ui->rotateAngle_spinBox->value();

    QPointF center(cx, cy);

    controller.rotateFigure(center, angle);
}

void MainWindow::on_scaleButton_clicked()
{
    float cx = ui->centerX_spinBox->value();
    float cy = ui->centerY_spinBox->value();

    float kx = ui->scaleX_spinBox->value();
    float ky = ui->scaleY_spinBox->value();

    QPointF center(cx, cy);
    QVector2D scale_v(kx, ky);

    controller.scaleFigure(center, scale_v);
}

void MainWindow::on_resetButton_clicked()
{
    controller.resetFigure();
}
