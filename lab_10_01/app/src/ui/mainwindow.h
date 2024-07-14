#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../model/controller.h"
#include "./ui_mainwindow.h"
#include <QMainWindow>
#include "canvas.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

  private slots:
    void on_aboutTaskAction_triggered();

    void on_cleanScreenButton_clicked();

    void on_colorChoiceButton_clicked();

    void on_showButton_clicked();

    void on_scaleButton_clicked();

    void on_rotateX_button_clicked();

    void on_rotateY_button_clicked();

    void on_rotateZ_button_clicked();

private:
    Ui::MainWindow *ui;
    Canvas *scene;
    QColor curColor;

    QVector<func_t> funcs;

    Controller controller;

    void setColor(const QColor &color);

    inline void errorMessage(const QString &message);
};
#endif // MAINWINDOW_H
