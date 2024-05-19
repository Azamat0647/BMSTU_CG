#include "mainwindow.h"
#include <QMessageBox>
#include <QColorDialog>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    controller(new QImage(1280, 720, QImage::Format_RGB32))
{
    setbuf(stdout, NULL);
    ui->setupUi(this);
    ui->graphicsView->setMouseTracking(true);
    auto tableModel = new QStandardItemModel;

    controller.setPointsModel(tableModel);
    ui->pointsTableView->setModel(tableModel);
    ui->pointsTableView->horizontalHeader()->
            setSectionResizeMode(QHeaderView::Stretch);
    ui->pointsTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->removeLastPointButton->setEnabled(false);
    ui->closePolygonButton->setEnabled(false);

    ui->addPointInputX_SB->setMaximum(controller.image()->width());
    ui->addPointInputY_SB->setMaximum(controller.image()->height());

    scene = new Canvas(controller);

    auto img = controller.image();
    scene->setSceneRect(0, 0, img->width(), img->height());
    scene->setBackgroundBrush(QBrush(Qt::white));
    ui->graphicsView->setScene(scene);

    connect(ui->delayCheckBox, &QCheckBox::stateChanged,
            ui->delaySpinBox, &QSpinBox::setEnabled);

    connect(&controller, &Controller::imageChanged, scene, &Canvas::updateScene);

    connect(&controller, &Controller::imageChanged, this, &MainWindow::pointsChanded);

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
    QString text = "Лабораторная работа №5 по дисциплине компьютерная графика,\n"
                    "на тему \"РЕАЛИЗАЦИЯ И ИССЛЕДОВАНИЕ АЛГОРИТМОВ"
                    " РАСТРОВОГО ЗАПОЛНЕНИЯ СПЛОШНЫХ ОБЛАСТЕЙ\"\n"
                    "Вариант 3: \"Алгоритм заполнения с перегородкой\"\n\n"
                    "Автор: Костоев Азамат";
    QMessageBox::about(this, title, text);
}


void MainWindow::pointsChanded()
{
    ui->removeLastPointButton->setEnabled(!controller.pointsIsEmpty());

    ui->closePolygonButton->setEnabled(controller.pointsCount() >= 3);
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
    if (!controller.pointsIsEmpty())
        errorMessage("закраска невозможна, так как имеется незамкнутый полигон\n");

    unsigned int delay = 0;
    if (ui->delayCheckBox->isChecked())
    {
        delay = ui->delaySpinBox->value();

        setAllButtonsEnabled(false);
    }

    QElapsedTimer timer;
    timer.start();
    controller.fill(curColor, delay);
    ui->fillTimeValueLabel->setText(QString::number(timer.elapsed() / 1000.) + " с");

    if (ui->delayCheckBox->isChecked())
        setAllButtonsEnabled(true);
}


void MainWindow::on_cleanScreenButton_clicked()
{
    controller.clearScreen();

    ui->addPointInputX_SB->setValue(0);
    ui->addPointInputY_SB->setValue(0);

    ui->fillTimeValueLabel->setText("0.00 с");
}


void MainWindow::on_removeLastPointButton_clicked()
{
    controller.removeLastPoint();
}

void MainWindow::setColor(const QColor &color)
{
    ui->colorView->setStyleSheet(QString("background-color: %1")
                                 .arg(color.name()));
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
    QString text =  "<b>ЛКМ</b> – добавление точки;<br>"
                    "<b>ПКМ</b> – замкнуть фигуру;<br>"
                    "<b>Ctrl</b> – горизонтальное/вертикальное ребро;<br>"
                    "<b>Backspace</b> – удаление последней вершины.";
    QMessageBox::about(this, title, text);
}

