#include "mainwindow.h"
#include <QColorDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), controller(new QImage(600, 600, QImage::Format_RGB32))
{
    setbuf(stdout, NULL);
    ui->setupUi(this);
    ui->graphicsView->setMouseTracking(true);
    auto tableModel = new QStandardItemModel;

    controller.setPointsModel(tableModel);
    ui->pointsTableView->setModel(tableModel);
    ui->pointsTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->pointsTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->closePolygonButton->setEnabled(false);

    scene = new Canvas(controller);

    auto img = controller.image();
    ui->addPointInputX_SB->setMaximum(img->width());
    ui->addPointInputY_SB->setMaximum(img->height());
    scene->setSceneRect(0, 0, img->width(), img->height());
    scene->setBackgroundBrush(QBrush(Qt::white));

    ui->graphicsView->setScene(scene);

    connect(ui->delayCheckBox, &QCheckBox::stateChanged, ui->delaySpinBox, &QSpinBox::setEnabled);

    connect(&controller, &Controller::imageChanged, scene, &Canvas::updateScene);
    connect(&controller, &Controller::imageChanged, this, &MainWindow::pointsChanded);
    connect(&controller, &Controller::seedPointChanged, this, &MainWindow::setSeedPoint);

    setColor(QColor("green"));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
}

void MainWindow::on_aboutTaskAction_triggered()
{
    QString title = "О программе";
    QString text = "Лабораторная работа №6 по дисциплине компьютерная графика,\n"
                   "на тему \"РЕАЛИЗАЦИЯ И ИССЛЕДОВАНИЕ АЛГОРИТМА ПОСТРОЧНОГО "
                   "ЗАТРАВОЧНОГО  ЗАПОЛНЕНИЯ СПЛОШНЫХ ОБЛАСТЕЙ\"\n\n"
                   "Автор: Костоев Азамат";
    QMessageBox::about(this, title, text);
}

void MainWindow::pointsChanded()
{
    ui->closePolygonButton->setEnabled(controller.pointsCount() >= 3);
}

void MainWindow::setSeedPoint(const QPoint &point)
{
    ui->seedPointValueLabel->setText(QString::asprintf("(%d, %d)", point.x(), point.y()));
}

void MainWindow::on_addPointButton_clicked()
{
    int x = ui->addPointInputX_SB->value();
    int y = ui->addPointInputY_SB->value();

    controller.addPoint(QPoint(x, y));
}

void MainWindow::on_closePolygonButton_clicked()
{
    controller.closePolygon();
}

void MainWindow::on_colorChoiceButton_clicked()
{
    setColor(QColorDialog::getColor(curColor));
}

void MainWindow::on_fillButton_clicked()
{
    unsigned int delay = 0;
    if (ui->delayCheckBox->isChecked())
    {
        delay = ui->delaySpinBox->value();

        setAllButtonsEnabled(false);
    }

    try
    {
        QElapsedTimer timer;
        timer.start();
        controller.fill(curColor, delay);
        ui->fillTimeValueLabel->setText(QString::number(timer.elapsed() / 1000.) + " с");
    }
    catch (const QString &message)
    {
        errorMessage(message);
    }

    if (ui->delayCheckBox->isChecked())
        setAllButtonsEnabled(true);
}

void MainWindow::on_removeLastPointButton_clicked()
{
    controller.removeLastPoint();
}

void MainWindow::setColor(const QColor &color)
{
    ui->colorView->setStyleSheet(QString("background-color: %1").arg(color.name()));
    curColor = color;
}

void MainWindow::errorMessage(const QString &message)
{
    QMessageBox msg;
    msg.setIcon(QMessageBox::Critical);
    msg.setWindowTitle("Ошибка");
    msg.setText(message);
    msg.exec();
}

void MainWindow::setAllButtonsEnabled(bool enable)
{
    ui->addPointButton->setEnabled(enable);
    ui->cleanScreenButton->setEnabled(enable);
    ui->fillButton->setEnabled(enable);
    ui->colorChoiceButton->setEnabled(enable);
}

void MainWindow::on_action_triggered()
{
    QString title = "Управление на канвасе";
    QString text = "<b>ЛКМ</b> – добавление точки;<br>"
                   "<b>ПКМ</b> – замкнуть фигуру;<br>"
                   "<b>Ctrl</b> – горизонтальное/вертикальное ребро;<br>"
                   "<b>Shift+ЛКМ</b> – установить затравочную точку;<br>"
                   "<b>Backspace</b> – удаление последней вершины.";
    QMessageBox::about(this, title, text);
}

void MainWindow::on_setSeedPointButton_clicked()
{
    int x = ui->addPointInputX_SB->value();
    int y = ui->addPointInputY_SB->value();

    controller.setSeedPoint(QPoint(x, y));
}

void MainWindow::on_cleanScreenButton_clicked()
{
    controller.clearScreen();

    ui->addPointInputX_SB->setValue(0);
    ui->addPointInputY_SB->setValue(0);

    ui->fillTimeValueLabel->setText(" ");
    ui->seedPointValueLabel->setText("Не задана");

    controller.resetSeedPoint();
}
