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
    auto tableModel = new QStandardItemModel;

    controller.setLinesModel(tableModel);
    ui->pointsTableView->setModel(tableModel);
    ui->pointsTableView->horizontalHeader()->
            setSectionResizeMode(QHeaderView::Stretch);
    ui->pointsTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    scene = new Canvas(controller);

    auto img = controller.image();
    scene->setSceneRect(0, 0, img->width(), img->height());
    scene->setBackgroundBrush(QBrush(Qt::white));

    ui->graphicsView->setScene(scene);

    connect(&controller, &Controller::imageChanged, scene, &Canvas::updateScene);
    connect(&controller, &Controller::cutterRectSetted, this, &MainWindow::setCutterRect);

    setResColor("#00ff00");
    setLineColor("black");
    setCutterColor("red");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
}


void MainWindow::on_aboutTaskAction_triggered()
{
    QString title = "О программе";
    QString text =  "Лабораторная работа №7 по дисциплине компьютерная графика,\n"
                    "на тему \"Реализация алгоритма отсечения отрезка регулярным отсекателем\"\n"
                    "Вариант №1: Простой алгоритм\n\n"
                    "Автор: Костоев Азамат";
    QMessageBox::about(this, title, text);
}


void MainWindow::setCutterRect(const QRect &rect)
{
    QString lt_label = QString::asprintf("ЛВ: (%d, %d)",
                                         rect.topLeft().x(), rect.topLeft().y());
    QString rb_label = QString::asprintf("ПН: (%d, %d)",
                                         rect.bottomRight().x(), rect.bottomRight().y());;

    ui->cutterValueLabel->setText(QString("%1; %2").arg(lt_label).arg(rb_label));
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
                    "<b>Backspace</b> – удалить последний отрезок.";
    QMessageBox::about(this, title, text);
}



void MainWindow::on_cleanScreenButton_clicked()
{
    controller.clearScreen();

    ui->lineBeginX_SB->setValue(0);
    ui->lineBeginY_SB->setValue(0);
    ui->lineEndX_SB->setValue(0);
    ui->lineEndY_SB->setValue(0);

    ui->rectTLPointX_SB->setValue(0);
    ui->rectTLPointY_SB->setValue(0);
    ui->rectRBPointX_SB->setValue(0);
    ui->rectRBPointY_SB->setValue(0);

    ui->cutterValueLabel->setText("Не задан");
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


void MainWindow::on_addCutterRectButton_clicked()
{
    int tl_x = ui->rectTLPointX_SB->value();
    int tl_y = ui->rectTLPointY_SB->value();

    int br_x = ui->rectRBPointX_SB->value();
    int br_y = ui->rectRBPointY_SB->value();

    controller.setCutterRect(QRect(QPoint(tl_x, tl_y), QPoint(br_x, br_y)));
}

