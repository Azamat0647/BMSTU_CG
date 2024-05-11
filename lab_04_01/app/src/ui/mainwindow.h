#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "../model/controller.h"
#include "./ui_mainwindow.h"

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

    void on_timeCompButton_clicked();

    void on_drawCircleSpectBtn_clicked();

    void circleParams_changed();

    void on_drawEllipseSpectrumBtn_clicked();

    void on_drawCircleBtn_clicked();

    void on_drawEllipseBtn_clicked();

  private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *pixmap_item;

    Controller controller;

    void updateScene();

    inline void errorMessage(const QString &message);
};
#endif // MAINWINDOW_H
