#include "mainwindow.h"

#include <QMessageBox>
#include <QtCharts>

const char *alg_titles[6] = {"Алглоритм Брезенхема", "Каноническое ур-ие", "Параметрическое ур-ие",
                             "Алгоритм ср. точки", "Library"};

enum circleParams_t
{
    NO_RB,
    NO_RE,
    NO_STEP,
    NO_COUNT
};

enum ellipseParams_t
{
    STEP_BY_RA,
    STEP_BY_RB
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), scene(new QGraphicsScene),
      controller(new QImage(600, 600, QImage::Format_RGB32))
{
    setbuf(stdout, NULL);
    ui->setupUi(this);

    scene->setSceneRect(0, 0, 600, 600);
    scene->setBackgroundBrush(QBrush(Qt::white));
    ui->graphicsView->setScene(scene);

    pixmap_item = scene->addPixmap(QPixmap::fromImage(*controller.image()));

    for (int i = 0; i <= STD; i++)
        ui->algorithmComboBox->addItem(alg_titles[i], i);

    ui->colorComboBox->addItem("Черный", QColor(Qt::black));
    ui->colorComboBox->addItem("Красный", QColor(Qt::red));
    ui->colorComboBox->addItem("Синий", QColor(Qt::blue));
    ui->colorComboBox->addItem("Цвет фона", QColor(Qt::white));

    ui->figureComboBox->addItem("Окружность");
    ui->figureComboBox->addItem("Эллипс");

    ui->circleSpectParamsCB->addItem("Без Rb", NO_RB);
    ui->circleSpectParamsCB->addItem("Без Re", NO_RE);
    ui->circleSpectParamsCB->addItem("Без шага", NO_STEP);
    ui->circleSpectParamsCB->addItem("Без количества", NO_COUNT);

    ui->ellipseSpectParamsCB->addItem("Шаг по Ra", STEP_BY_RA);
    ui->ellipseSpectParamsCB->addItem("Шаг по Rb", STEP_BY_RB);

    connect(ui->figureComboBox, QOverload<int>::of(&QComboBox::activated), ui->CircleEllipseSW,
            &QStackedWidget::setCurrentIndex);

    connect(ui->circleSpectParamsCB, QOverload<int>::of(&QComboBox::activated), this,
            &MainWindow::circleParams_changed);

    ui->CircleEllipseSW->setCurrentIndex(ui->figureComboBox->currentIndex());
    circleParams_changed();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
}

void MainWindow::circleParams_changed()
{
    int param = ui->circleSpectParamsCB->currentData().toInt();

    ui->circleSpectRbSB->setEnabled(param != NO_RB);
    ui->circleSpectReSB->setEnabled(param != NO_RE);
    ui->circleSpectStepSB->setEnabled(param != NO_STEP);
    ui->circleSpectCountSB->setEnabled(param != NO_COUNT);
}

void MainWindow::on_aboutTaskAction_triggered()
{
    QString title = "О программе";
    QString text = "Лабораторная работа №4 по дисциплине компьютерная графика";
    QMessageBox::about(this, title, text);
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

void MainWindow::on_drawCircleBtn_clicked()
{
    int cx = ui->circleCenterX_SB->value();
    int cy = ui->circleCenterY_SB->value();

    int r = ui->circleRadiusSB->value();

    QPoint center(cx, cy);

    circle_t circle = {.radius = r, .center = center};

    int alg = ui->algorithmComboBox->currentData().toInt();
    QColor color = ui->colorComboBox->currentData().value<QColor>();

    controller.drawCircle(circle, alg, color);
    updateScene();
}

void MainWindow::on_drawEllipseBtn_clicked()
{
    int cx = ui->ellipseCenterX_SB->value();
    int cy = ui->ellipseCenterY_SB->value();

    int ra = ui->ellipseRa_SB->value();
    int rb = ui->ellipseRb_SB->value();

    QPoint center(cx, cy);

    ellipse_t ellipse = {.ra = ra, .rb = rb, .center = center};

    int alg = ui->algorithmComboBox->currentData().toInt();
    QColor color = ui->colorComboBox->currentData().value<QColor>();

    controller.drawEllipse(ellipse, alg, color);
    updateScene();
}

void MainWindow::on_drawCircleSpectBtn_clicked()
{
    int Rb = ui->circleSpectRbSB->value();
    int Re = ui->circleSpectReSB->value();
    int step = ui->circleSpectStepSB->value();
    int count = ui->circleSpectCountSB->value();

    int param = ui->circleSpectParamsCB->currentData().toInt();

    switch (param)
    {
    case NO_RB:
        Rb = Re - step * (count - 1);

        if (Rb < 0)
        {
            errorMessage("При заданых параметрах радиусы некоторых "
                         "окружностей спектра получаются отрицательными");
            return;
        }
        break;
    case NO_STEP:
        if (count == 0)
        {
            errorMessage("Количество окружностей в спектре не может "
                         "быть нулевым");
            return;
        }

        step = (Re - Rb) / count;

        break;
    case NO_COUNT:
        if (step == 0)
        {
            errorMessage("шаг спектра не может быть нулевым");
            return;
        }

        count = abs(Re - Rb) / step + 1;

        if (Re < Rb)
            step *= -1;

        break;
    }

    circle_spectrum_t spect = {.Rbegin = Rb, .step = step, .count = count};

    int alg = ui->algorithmComboBox->currentData().toInt();
    QColor color = ui->colorComboBox->currentData().value<QColor>();

    controller.drawCircleSpectrum(spect, alg, color);
    updateScene();
}

void MainWindow::on_drawEllipseSpectrumBtn_clicked()
{
    int RaBeg = ui->ellipseSpectRaBegin_SB->value();
    int RbBeg = ui->ellipseSpectRbBegin_SB->value();
    int step = ui->ellipseSpectStepSB->value();
    int count = ui->ellipseSpectCountSB->value();

    if (RaBeg == 0 || RbBeg == 0)
    {
        errorMessage("Полуоси эллипса должны быть больше нуля");
        return;
    }

    ellipse_spectrum_t spect = {.RaBegin = RaBeg, .RbBegin = RbBeg, .step = step, .count = count};

    int param = ui->ellipseSpectParamsCB->currentData().toInt();

    if (param == STEP_BY_RB)
        spect.stepByRb = true;

    int alg = ui->algorithmComboBox->currentData().toInt();
    QColor color = ui->colorComboBox->currentData().value<QColor>();

    controller.drawEllipseSpectrum(spect, alg, color);
    updateScene();
}

void MainWindow::on_timeCompButton_clicked()
{
    int figure = ui->figureComboBox->currentIndex();

    QChart *chart = new QChart;

    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

    chart->setTitle(
        QString("Сравнение времени работы алгоритмов<br>построения %1").arg((figure) ? "эллипса" : "окружности"));

    for (int alg = 0; alg <= STD; alg++)
    {
        QList<QPointF> times;

        if (figure == 0)
            times = controller.circleAlgorithmTimes(alg);
        else
            times = controller.ellipseAlgorithmTimes(alg);

        auto series = new QLineSeries;

        series->append(times);

        series->setName(alg_titles[alg]);
        chart->addSeries(series);
    }
    controller.clearScreen();
    chart->createDefaultAxes();

    auto axisX = dynamic_cast<QValueAxis *>(chart->axes()[0]);
    auto axisY = dynamic_cast<QValueAxis *>(chart->axes()[1]);

    axisX->setTitleText((figure) ? "Полуось Ra" : "Радиус");
    axisY->setTitleText("Время, мс");

    axisY->setLabelFormat("%d");
    axisY->applyNiceNumbers();

    auto view = new QChartView(chart);
    view->resize(700, 500);
    view->setMinimumSize(400, 400);
    view->show();
}

void MainWindow::updateScene()
{
    pixmap_item->setPixmap(QPixmap::fromImage(*controller.image()));
}
