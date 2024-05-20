#include <string>
#include <stdio.h>

#include <QImage>
#include <QtCharts>
#include "controller.h"

#define ERROR_VALUE -1
#define ERROR_COMMAND -2

void errors_handler(int error_code)
{
    if (error_code == ERROR_VALUE)
        printf("Ошибка, некорректные входные данные\n");
    else if (error_code == ERROR_COMMAND)
        printf("Ошибка, Неизвестная команда\n");
}

int main(int argc, char *argv[])
{
    setbuf(stdout, NULL);

    int code = 0;
    QApplication a(argc, argv);

    QChartView *view = new QChartView;
    Controller controller(view);

    view->resize(600, 600);

    std::string filename = "image.jpeg";

    int i = 1;

    setlocale(LC_NUMERIC, "C");
    for (; i < argc; i++)
    {
        std::string flag(argv[i]);
        if (flag == "-o")
        {
            filename = argv[++i];
        }
        else
            break;
    }

    for (; i < argc && !code; i++)
    {
        std::string command(argv[i]);

        if (command == "move")
        {
            float mx, my;

            if (sscanf(argv[++i], "%f", &mx) != 1 ||
                    sscanf(argv[++i], "%f", &my) != 1)
            {
                code = ERROR_VALUE;
                continue;
            }

            QVector2D movev(mx, my);

            controller.moveFigure(movev);
        }
        else if (command == "scale")
        {
            float cx, cy;
            float kx, ky;

            if (sscanf(argv[++i], "%f", &cx) != 1 ||
                    sscanf(argv[++i], "%f", &cy) != 1)
            {
                code = ERROR_VALUE;
                continue;
            }

            if (sscanf(argv[++i], "%f", &kx) != 1 ||
                    sscanf(argv[++i], "%f", &ky) != 1)
            {
                code = ERROR_VALUE;
                continue;
            }

            QPointF center(cx, cy);
            QVector2D scalev(kx, ky);

            controller.scaleFigure(center, scalev);
        }
        else if (command == "rotate")
        {
            float cx, cy;
            float angle;

            if (sscanf(argv[++i], "%f", &cx) != 1 ||
                    sscanf(argv[++i], "%f", &cy) != 1)
            {
                code = ERROR_VALUE;
                continue;
            }

            if (sscanf(argv[++i], "%f", &angle) != 1)
            {
                code = ERROR_VALUE;
                continue;
            }

            QPointF center(cx, cy);

            controller.rotateFigure(center, angle);
        }
        else
            code = ERROR_COMMAND;
    }

    if (code)
    {
        errors_handler(code);
        return code;
    }

    QImage image = view->grab().toImage();

    image.save(filename.c_str(), "JPEG");

    return 0;
}
