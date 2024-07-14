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
    void setCutterRect(const QRect &rect);

    void on_aboutTaskAction_triggered();

    void on_cleanScreenButton_clicked();

    void on_action_triggered();

    void on_cutterColorChoiceBtn_clicked();

    void on_linesColorChoiceBtn_clicked();

    void on_resColorChoiceBtn_clicked();

    void on_cutoffButton_clicked();

    void on_addLineButton_clicked();

    void on_addCutterRectButton_clicked();

private:
    Ui::MainWindow *ui;
    Canvas *scene;
    QColor curColor;

    Controller controller;

    void setLineColor(const QColor &color);
    void setCutterColor(const QColor &color);
    void setResColor(const QColor &color);

    inline void errorMessage(const QString &message);
};
#endif // MAINWINDOW_H
