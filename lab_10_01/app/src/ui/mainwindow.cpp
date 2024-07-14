#include "mainwindow.h"
#include <QMessageBox>
#include <QColorDialog>


const char *func_titles[6] =
{
    "Алглоритм Брезенхема",
    "Каноническое ур-ие",
    "Параметрическое ур-ие",
    "Алгоритм ср. точки",
    "Library"
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    controller(new QImage(800, 800, QImage::Format_RGB32))
{
    setbuf(stdout, NULL);
    ui->setupUi(this);

    auto img = controller.image();

    scene = new Canvas(*img);
    scene->setSceneRect(0, 0, img->width(), img->height());
    scene->setBackgroundBrush(QBrush(Qt::white));

    ui->graphicsView->setScene(scene);

    funcs << [](qreal x, qreal z){ return qSin(x) * qCos(z); };
    ui->funcComboBox->addItem("sin(x) * cos(z)");

    funcs << [](qreal x, qreal z){ return qCos(x * qSin(z)); };
    ui->funcComboBox->addItem("cos(x * sin(z))");

    funcs << [](qreal x, qreal z){ return qCos(qSqrt(qPow(x, 2) + qPow(z, 2))); };
    ui->funcComboBox->addItem("cos(sqrt(x^2 + z^2))");

    funcs << [](qreal x, qreal z){ return qPow(qSin(x), 2) + qPow(qCos(z), 2); };
    ui->funcComboBox->addItem("sin(x)^2 + cos(z)^2");

    connect(&controller, &Controller::imageChanged, scene, &Canvas::updateScene);

    setColor("#0051ff");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
}


void MainWindow::on_aboutTaskAction_triggered()
{
    QString title = "О программе";
    QString text =  "Лабораторная работа №10 по дисциплине компьютерная графика,\n"
                    "на тему \"Реализация алгоритма отсечения отрезка произвольным выпуклым отсекателем.\n"
                    "(Алгоритм Кируса-Бека)\"\n\n"
                    "Автор: Костоев Азамат";
    QMessageBox::about(this, title, text);
}


void MainWindow::setColor(const QColor &color)
{
    ui->colorChoiceButton->setStyleSheet(QString("background-color: %1")
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



void MainWindow::on_cleanScreenButton_clicked()
{
    controller.clearScreen();
}



void MainWindow::on_colorChoiceButton_clicked()
{
    QColor color = QColorDialog::getColor(curColor);

    setColor(color);
}


void MainWindow::on_showButton_clicked()
{
    qreal from, to, step;

    from = ui->fromX_spinBox->value();
    to = ui->toX_spinBox->value();
    step = ui->stepX_spinBox->value();

    range_t xrange = {from, to, step};

    from = ui->fromZ_spinBox->value();
    to = ui->toZ_spinBox->value();
    step = ui->stepZ_spinBox->value();

    range_t zrange = {from, to, step};
    int fi = ui->funcComboBox->currentIndex();

    controller.draw(xrange, zrange, funcs[fi], curColor);
}


void MainWindow::on_scaleButton_clicked()
{
    qreal k = ui->scaleSpinBox->value();
    controller.scale(k);
    on_showButton_clicked();
}


void MainWindow::on_rotateX_button_clicked()
{
    int angle = ui->rotateX_spinBox->value();
    controller.rotateX(angle);
    on_showButton_clicked();
}


void MainWindow::on_rotateY_button_clicked()
{
    int angle = ui->rotateY_spinBox->value();
    controller.rotateY(angle);
    on_showButton_clicked();
}


void MainWindow::on_rotateZ_button_clicked()
{
    int angle = ui->rotateZ_spinBox->value();
    controller.rotateZ(angle);
    on_showButton_clicked();
}

