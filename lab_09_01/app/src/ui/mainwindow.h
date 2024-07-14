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
    void updateButtonsState();

    void on_aboutTaskAction_triggered();
    void on_action_triggered();

    void on_cleanScreenButton_clicked();

    void on_cutterColorChoiceBtn_clicked();
    void on_polygonColorChoiceBtn_clicked();
    void on_resColorChoiceBtn_clicked();

    void on_cutoffButton_clicked();

    void on_addPolygonPointButton_clicked();
    void on_addCutterPointButton_clicked();

    void on_closeCutterButton_clicked();
    void on_closePolygonButton_clicked();

    void on_removeLastCutterPointBtn_clicked();
    void on_removeLastPolygonPointBtn_clicked();


private:
    Ui::MainWindow *ui;
    Canvas *scene;

    Controller controller;

    void setPolygonColor(const QColor &color);
    void setCutterColor(const QColor &color);
    void setResColor(const QColor &color);

    inline void errorMessage(const QString &message);
};
#endif // MAINWINDOW_H
