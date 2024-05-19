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

    void pointsChanded();

    void on_aboutTaskAction_triggered();

    void on_addPointButton_clicked();

    void on_closePolygonButton_clicked();

    void on_colorChoiceButton_clicked();

    void on_fillButton_clicked();

    void on_cleanScreenButton_clicked();

    void on_removeLastPointButton_clicked();

    void on_action_triggered();

private:
    Ui::MainWindow *ui;
    Canvas *scene;
    QColor curColor;

    Controller controller;

    void setColor(const QColor &color);
    void setAllButtonsEnabled(bool enable);

    inline void errorMessage(const QString &message);
};
#endif // MAINWINDOW_H
