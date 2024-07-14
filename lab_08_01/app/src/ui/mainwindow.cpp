#include "mainwindow.h"
#include <QMessageBox>
#include <QColorDialog>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    controller(new QImage(800, 800, QImage::Format_RGB32))
{
    setbuf(stdout, NULL);
    ui->setupUi(this);
    ui->graphicsView->setMouseTracking(true);

    auto cutterTableModel = new QStandardItemModel;
    auto linesTableModel = new QStandardItemModel;

    controller.setLinesModel(linesTableModel);
    controller.setCutterModel(cutterTableModel);

    ui->linesTableView->setModel(linesTableModel);
    ui->linesTableView->horizontalHeader()->
            setSectionResizeMode(QHeaderView::Stretch);
    ui->linesTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->cutterTableView->setModel(cutterTableModel);
    ui->cutterTableView->horizontalHeader()->
            setSectionResizeMode(QHeaderView::Stretch);
    ui->cutterTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    scene = new Canvas(controller);

    auto img = controller.image();
    scene->setSceneRect(0, 0, img->width(), img->height());
    scene->setBackgroundBrush(QBrush(Qt::white));

    ui->graphicsView->setScene(scene);

    connect(&controller, &Controller::imageChanged, scene, &Canvas::updateScene);
    connect(&controller, &Controller::imageChanged, this, &MainWindow::updateButtonsState);

    updateButtonsState();

    setResColor("#00ff00");
    setLineColor("#0051ff");
    setCutterColor("red");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
}

void MainWindow::updateButtonsState()
{
    ui->removeLastLineButton->setEnabled(!controller.linesIsEmpty());
    ui->removeLastCutterPointBtn->setEnabled(!controller.pointsIsEmpty());

    ui->closeCutterButton->setEnabled(controller.pointsCount() >= 3);
}


void MainWindow::on_aboutTaskAction_triggered()
{
    QString title = "О программе";
    QString text =  "Лабораторная работа №8 по дисциплине компьютерная графика,\n"
                    "на тему \"Реализация алгоритма отсечения отрезка произвольным выпуклым отсекателем.\n"
                    "(Алгоритм Кируса-Бека)\"\n\n"
                    "Автор: Костоев Азамат";
    QMessageBox::about(this, title, text);
}


void MainWindow::setResColor(const QColor &color)
{
    ui->resColorChoiceBtn->setStyleSheet(QString("background-color: %1")
                                 .arg(color.name()));
    controller.setResColor(color);
}

void MainWindow::setCutterColor(const QColor &color)
{
    ui->cutterColorChoiceBtn->setStyleSheet(QString("background-color: %1")
                                 .arg(color.name()));
    controller.setCutterColor(color);
}

void MainWindow::setLineColor(const QColor &color)
{
    ui->linesColorChoiceBtn->setStyleSheet(QString("background-color: %1")
                                 .arg(color.name()));
    controller.setLineColor(color);
}

void MainWindow::errorMessage(const QString &message)
{
    QMessageBox msg;
    msg.setIcon(QMessageBox::Critical);
    msg.setWindowTitle("Ошибка");
    msg.setText(message);
    msg.exec();
}



void MainWindow::on_action_triggered()
{
    QString title = "Управление на канвасе";
    QString text =  "<b>ЛКМ</b> – добавление отрезка;<br>"
                    "<b>ПКМ</b> – задание отсекателя;<br>"
                    "<b>Удерживание Ctrl</b> – горизонтальный/вертикальный отрезок;<br>"
                    "<b>Backspace</b> – удалить последний отрезок/вершину.";
    QMessageBox::about(this, title, text);
}



void MainWindow::on_cleanScreenButton_clicked()
{
    controller.clearScreen();

    ui->lineBeginX_SB->setValue(0);
    ui->lineBeginY_SB->setValue(0);
    ui->lineEndX_SB->setValue(0);
    ui->lineEndY_SB->setValue(0);

    ui->cutterPointX_SB->setValue(0);
    ui->cutterPointY_SB->setValue(0);
}



void MainWindow::on_cutterColorChoiceBtn_clicked()
{
    QColor color = QColorDialog::getColor(controller.cutterColor());

    setCutterColor(color);
}


void MainWindow::on_linesColorChoiceBtn_clicked()
{
    QColor color = QColorDialog::getColor(controller.lineColor());

    setLineColor(color);
}


void MainWindow::on_resColorChoiceBtn_clicked()
{
    QColor color = QColorDialog::getColor(controller.resColor());

    setResColor(color);
}


void MainWindow::on_cutoffButton_clicked()
{
    try
    {
        controller.cutOff();
    }
    catch (const QString &message)
    {
        errorMessage(message);
    }
}



void MainWindow::on_addLineButton_clicked()
{
    int x1 = ui->lineBeginX_SB->value();
    int y1 = ui->lineBeginY_SB->value();

    int x2 = ui->lineEndX_SB->value();
    int y2 = ui->lineEndY_SB->value();

    controller.addLine(QLine(x1, y1, x2, y2));
}



void MainWindow::on_addCutterPointButton_clicked()
{
    int x = ui->cutterPointX_SB->value();
    int y = ui->cutterPointY_SB->value();

    controller.addCutterPoint(QPoint(x, y));
}


void MainWindow::on_closeCutterButton_clicked()
{
    controller.closeCutterPolygon();
}


void MainWindow::on_removeLastCutterPointBtn_clicked()
{
    controller.removeLastCutterPoint();
}


void MainWindow::on_removeLastLineButton_clicked()
{
    controller.removeLastLine();
}

