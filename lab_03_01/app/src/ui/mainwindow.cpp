#include "mainwindow.h"
#include <QMessageBox>
#include <QtCharts>

const char *alg_titles[6] = {"ЦДА", "Брезенхем (int)", "Брезенхем (float)", "Брезенхем (сглаживание)", "Ву", "Library"};

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), scene(new QGraphicsScene)
{
    setbuf(stdout, NULL);
    ui->setupUi(this);

    ui->graphicsView->setScene(scene);

    pixmap_item = scene->addPixmap(QPixmap::fromImage(*controller.image()));

    auto *model = new QStringListModel;

    QStringList list;

    for (auto &alg_title : alg_titles)
    {
        list << alg_title;
    }

    model->setStringList(list);

    for (int i = 0; i <= STD; i++)
        ui->algorithmComboBox->addItem(alg_titles[i], i);

    ui->colorComboBox->addItem("Черный", QColor(Qt::black));
    ui->colorComboBox->addItem("Красный", QColor(Qt::red));
    ui->colorComboBox->addItem("Синий", QColor(Qt::blue));
    ui->colorComboBox->addItem("Цвет фона", QColor(Qt::white));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
}


void MainWindow::on_aboutTaskAction_triggered()
{
    QString title = "О программе";
    QString text = "Лабороторная работа №3 по дисциплине \"Компьютерная графика\""
                   " на тему \"рисование отрезков с использованием различных алгоритмов\""
                   "\n\nАвтор Костоев Азамат";
    QMessageBox::about(this, title, text);
}

void MainWindow::on_drawLineButton_clicked()
{
    QPoint begin(ui->beginPointXSpinBox->value(), ui->beginPointYSpinBox->value());

    QPoint end(ui->endPointXSpinBox->value(), ui->endPointYSpinBox->value());

    if (begin == end)
    {
        errorMessage("Точки начала и конца отрезка не должны совпадать!\n");
        return;
    }

    QColor color = ui->colorComboBox->currentData().value<QColor>();

    QLine line(begin, end);

    int alg_type = ui->algorithmComboBox->currentData().toInt();

    controller.drawLine(line, alg_type, color);
    updateScene();
}

void MainWindow::updateScene()
{
    pixmap_item->setPixmap(QPixmap::fromImage(*controller.image()));
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
    updateScene();
}

void MainWindow::on_drawSpectrumButton_clicked()
{
    spectrum_t spect = {.radius = ui->radiusSpinBox->value(), .step = ui->stepSpinBox->value()};

    if (spect.radius == 0)
    {
        errorMessage("Радиус должен быть больше нуля\n");
    }

    QColor color = ui->colorComboBox->currentData().value<QColor>();

    int alg_type = ui->algorithmComboBox->currentData().toInt();

    controller.drawSpectrum(spect, alg_type, color);
    updateScene();
}

void MainWindow::on_timeCompButton_clicked()
{
    QChart *chart = new QChart;

    spectrum_t spect = {.radius = 200, .step = 20};

    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);
    chart->setTitle("Сравнение времени работы алгоритмов<br>Длина отрезка: 200 Шаг поворота: 20");

    auto set = new QBarSet("Время без отрисовки");

    auto series = new QBarSeries;

    auto times = controller.algorithmsTimes(spect, 1000);
    double maxTime = *std::max_element(times.begin(), times.end());
    set->append(times);

    series->append(set);
    chart->addSeries(series);

    QStringList categories;

    for (auto &alg_title : alg_titles)
        categories << alg_title;

    auto axisX = new QBarCategoryAxis;
    axisX->append(categories);
    axisX->setTitleText("Алгоритм рисования");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    auto axisY = new QValueAxis;
    axisY->setRange(0, 1.2 * maxTime);
    axisY->setTitleText("Время, мкс");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    auto view = new QChartView(chart);

    view->resize(700, 500);

    view->show();
}

void MainWindow::on_gradCompButton_clicked()
{
    QChart *chart = new QChart;

    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);
    chart->setTitle("Сравнение времени работы алгоритмов<br>Длина отрезка: 200 Шаг поворота: 15");

    spectrum_t spect = {.radius = 200, .step = 15};

    for (int alg = 0; alg < STD; alg++)
    {
        QList<QPointF> list = controller.algorithmsStepsCount(spect, alg);

        auto series = new QLineSeries;

        series->append(list);

        series->setName(alg_titles[alg]);
        chart->addSeries(series);
    }

    chart->createDefaultAxes();

    auto axisX = dynamic_cast<QValueAxis *>(chart->axes()[0]);
    auto axisY = dynamic_cast<QValueAxis *>(chart->axes()[1]);

    axisX->setTitleText("Угол");
    axisY->setTitleText("Кол-во ступенек");

    axisY->setLabelFormat("%d");
    axisY->applyNiceNumbers();

    auto view = new QChartView(chart);

    view->resize(700, 500);

    view->show();
}
