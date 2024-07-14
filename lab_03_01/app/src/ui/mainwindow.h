#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../model/controller.h"
#include "./ui_mainwindow.h"
#include <QMainWindow>

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

    void on_drawLineButton_clicked();

    void on_cleanScreenButton_clicked();

    void on_drawSpectrumButton_clicked();

    void on_timeCompButton_clicked();

    void on_gradCompButton_clicked();

  private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *pixmap_item;

    Controller controller;

    void updateScene();

    inline void errorMessage(const QString &message);
};
#endif // MAINWINDOW_H
