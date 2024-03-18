#include "mainwindow.h"
#include "./itemdelegate.h"
#include <QDoubleValidator>
#include <QFileDialog>
#include <QList>
#include <QMessageBox>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  pointsTableModel = new QStandardItemModel(0, 2);

  canvas = new Canvas(ui->frame);
  ui->verticalLayout_2->addWidget(canvas);

  pointsTableModel->setHorizontalHeaderLabels({"X", "Y"});

  ui->PointsListView->setModel(pointsTableModel);
  ui->PointsListView->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);
  ui->PointsListView->setItemDelegate(new ItemDelegate);

  QDoubleValidator *validator = create_validator();

  ui->x_input->setValidator(validator);
  ui->y_input->setValidator(validator);

  connect(ui->PointsListView->selectionModel(),
          &QItemSelectionModel::selectionChanged, this,
          &MainWindow::slot_selection_changed);

  connect(dynamic_cast<ItemDelegate *>(ui->PointsListView->itemDelegate()),
          &ItemDelegate::item_changed, this, &MainWindow::slot_item_changed);
}

MainWindow::~MainWindow() {
  delete ui;
  delete pointsTableModel;
  delete canvas;
}

void MainWindow::error_message(QString message_text) {
  QMessageBox msgBox;
  msgBox.setText(message_text);
  msgBox.setIcon(QMessageBox::Critical);
  msgBox.exec();
}

void MainWindow::add_point_to_table(QString x, QString y) {
  const QList<QStandardItem *> row = {new QStandardItem(x),
                                      new QStandardItem(y)};

  pointsTableModel->appendRow(row);
}

void MainWindow::clear_table() {
  pointsTableModel->removeRows(0, pointsTableModel->rowCount());
}

void MainWindow::on_addPointBtn_clicked() {
  QString x, y;
  x = ui->x_input->text();
  y = ui->y_input->text();

  if (x.isEmpty() or y.isEmpty()) {
    QMessageBox msgBox;
    msgBox.setText("Пожалуйста, заполните все поля ввода!");
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.exec();
    return;
  }

  if (canvas->getPoints()->add_point(QPointF(x.toFloat(), y.toFloat()))) {
    error_message(POINT_ALREADY_EXIST_TEXT);
    return;
  }

  add_point_to_table(x, y);
  canvas->update_display();

  ui->x_input->clear();
  ui->y_input->clear();
}

void MainWindow::on_removePointBtn_clicked() {
  QItemSelectionModel *selModel = ui->PointsListView->selectionModel();
  int point_ind = selModel->selectedIndexes()[0].row();

  pointsTableModel->removeRow(point_ind);
  canvas->getPoints()->remove_point(point_ind);

  ui->PointsListView->clearSelection();

  canvas->update_display();
}

void MainWindow::slot_selection_changed(const QItemSelection &selected,
                                        const QItemSelection &deselected) {
  bool isSelected = selected.indexes().size() > 0;

  ui->removePointBtn->setEnabled(isSelected);
}

void MainWindow::slot_item_changed(const QModelIndex &index,
                                   QString previous_value) {
  float x =
      pointsTableModel->data(pointsTableModel->index(index.row(), 0)).toFloat();
  float y =
      pointsTableModel->data(pointsTableModel->index(index.row(), 1)).toFloat();

  if (canvas->getPoints()->change_point(index.row(), QPoint(x, y))) {
    error_message(POINT_ALREADY_EXIST_TEXT);
    pointsTableModel->setData(index, previous_value);
    return;
  }
  canvas->update_display();
}

void MainWindow::on_find_solution_button_clicked() { canvas->find_triangle(); }

void MainWindow::on_clearDisplayBtn_clicked() {
  clear_table();
  canvas->clear();
}

void MainWindow::on_fileImportAction_triggered() {
  QString fileName = QFileDialog::getOpenFileName(this);

  QFile f(fileName);

  if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
    return;

  QDoubleValidator *val = create_validator();

  while (!f.atEnd()) {
    QString line = f.readLine().trimmed();

    QStringList list = line.split(" ");
    int pos;

    if ((list.length() < 2) or !val->validate(list[0], pos) or
        !val->validate(list[1], pos)) {
      clear_table();
      canvas->getPoints()->clear_points();
      error_message("Ошибка чтения файла! Недопустимый формат");

      break;
    }

    QString x = list[0];
    QString y = list[1];

    if (canvas->getPoints()->add_point(QPointF(x.toFloat(), y.toFloat())))
      continue;

    add_point_to_table(x, y);
  }

  f.close();
  delete val;
  canvas->update_display();
}

void MainWindow::on_aboutTaskAction_triggered() {
  QString title = "Условие задачи, вариант 24";
  QString text = "На плоскости дано множество точек. Найти такой треугольник"
                 " с вершинами в этих точках, у которого сумма расстояний от"
                 " точки пересечения высот до координатных осей максимальна";
  QMessageBox::about(this, title, text);
}
