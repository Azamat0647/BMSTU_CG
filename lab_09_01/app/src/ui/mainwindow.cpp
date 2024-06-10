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
    auto polygonTableModel = new QStandardItemModel;

    controller.setPolygonModel(polygonTableModel);
    controller.setCutterModel(cutterTableModel);

    ui->polygonTableView->setModel(polygonTableModel);
    ui->polygonTableView->horizontalHeader()->
            setSectionResizeMode(QHeaderView::Stretch);
    ui->polygonTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

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
    setPolygonColor("#0051ff");
    setCutterColor("red");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
}

void MainWindow::updateButtonsState()
{
    ui->removeLastPolygonPointBtn->setEnabled(!controller.polygonPointsIsEmpty());
    ui->removeLastCutterPointBtn->setEnabled(!controller.cutterPointsIsEmpty());

    ui->closeCutterButton->setEnabled(controller.cutterPointsCount() >= 3);
    ui->closePolygonButton->setEnabled(controller.polygonPointsCount() >= 3);
}


void MainWindow::on_aboutTaskAction_triggered()
{
    QString title = "О программе";
    QString text =  "Лабораторная работа №9 по дисциплине компьютерная графика,\n"
                    "на тему \"ОТСЕЧЕНИЕ ПРОИЗВОЛЬНОГО МНОГОУГОЛЬНИКА ВЫПУКЛЫМ ОТСЕКАТЕЛЕМ "
                    "(АЛГОРИТМ САЗЕРЛЕНДА-ХОДЖМЕНА)\"\n\n"
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

void MainWindow::setPolygonColor(const QColor &color)
{
    ui->polygonColorChoiceBtn->setStyleSheet(QString("background-color: %1")
                                             .arg(color.name()));
    controller.setPolygonColor(color);
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
    QString text =  "<b>ЛКМ</b> – добавление многоугольника;<br>"
                    "<b>ПКМ</b> – задание отсекателя;<br>"
                    "<b>СКМ</b> – замкнуть отсекатель/многоугольник;<br>"
                    "<b>Удерживание Ctrl</b> – горизонтальное/вертикальное ребро;<br>"
                    "<b>Backspace</b> – удалить последюю вершину отсекателя/многоугольника.";
    QMessageBox::about(this, title, text);
}



void MainWindow::on_cleanScreenButton_clicked()
{
    controller.clearScreen();

    ui->polygonPointX_SB->setValue(0);
    ui->polygonPointY_SB->setValue(0);

    ui->cutterPointX_SB->setValue(0);
    ui->cutterPointY_SB->setValue(0);
}



void MainWindow::on_cutterColorChoiceBtn_clicked()
{
    QColor color = QColorDialog::getColor(controller.cutterColor());

    setCutterColor(color);
}


void MainWindow::on_polygonColorChoiceBtn_clicked()
{
    QColor color = QColorDialog::getColor(controller.polygonColor());

    setPolygonColor(color);
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



void MainWindow::on_addPolygonPointButton_clicked()
{
    int x = ui->polygonPointX_SB->value();
    int y = ui->polygonPointY_SB->value();

    controller.addPolygonPoint(QPoint(x, y));
}


void MainWindow::on_addCutterPointButton_clicked()
{
    int x = ui->cutterPointX_SB->value();
    int y = ui->cutterPointY_SB->value();

    controller.addCutterPoint(QPoint(x, y));
}


void MainWindow::on_closeCutterButton_clicked()
{
    controller.closeCutter();
}

void MainWindow::on_closePolygonButton_clicked()
{
    controller.closePolygon();
}


void MainWindow::on_removeLastCutterPointBtn_clicked()
{
    controller.removeLastCutterPoint();
}

void MainWindow::on_removeLastPolygonPointBtn_clicked()
{
    controller.removeLastPolygonPoint();
}


