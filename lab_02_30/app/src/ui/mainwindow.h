#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "./ui_mainwindow.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_aboutTaskAction_triggered();

    void on_moveButton_clicked();

    void on_rotateButton_clicked();

    void on_scaleButton_clicked();

    void on_resetButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
