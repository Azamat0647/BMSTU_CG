#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "./canvas.h"
#include "./ui_mainwindow.h"
#include <QMainWindow>
#include <QStandardItem>
#include <QStandardItemModel>

#define POINT_ALREADY_EXIST_TEXT "Такая точка уже существует!"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

  // void point_already_exist_error();

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  void error_message(QString message_text);

  void add_point_to_table(QString x, QString y);

  void clear_table();

private slots:

  void slot_selection_changed(const QItemSelection &selected,
                              const QItemSelection &deselected);

  void slot_item_changed(const QModelIndex &index, QString previous_value);

  void on_addPointBtn_clicked();

  void on_removePointBtn_clicked();

  void on_find_solution_button_clicked();

  void on_clearDisplayBtn_clicked();

  void on_fileImportAction_triggered();

  void on_aboutTaskAction_triggered();

private:
  Ui::MainWindow *ui;
  QStandardItemModel *pointsTableModel;
  Canvas *canvas;
};
#endif // MAINWINDOW_H
