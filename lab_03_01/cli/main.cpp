#include <string>
#include <stdio.h>

#include <QImage>
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

    const char *alg_titles[6] = {"ЦДА", "Брезенхем (int)", "Брезенхем (float)", "Брезенхем (сглаживание)", "Ву", "Library"};

    int code = 0;
    QApplication a(argc, argv);

    QImage *image = new QImage(800, 800, QImage::Format_RGB32);
    Controller controller(image);

    int alg = DDA;
    QColor color;

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
        else if (flag == "--color" || flag == "-c")
        {
            color = QColor(argv[++i]);
        }
        else if (flag == "--alg" || flag == "-a")
        {
            std::string alg_name = argv[++i];

            for (int i = 0; i <= STD; i++)
            {
                if (alg_name == alg_titles[i])
                    alg = i;
            }
        }
        else
            break;
    }

    for (; i < argc && !code; i++)
    {
        std::string command(argv[i]);

        if (command == "draw-line")
        {
            int x, y;
            QLine line;

            if (sscanf(argv[++i], "%d", &x) != 1 ||
                    sscanf(argv[++i], "%d", &y) != 1)
            {
                code = ERROR_VALUE;
                continue;
            }
            line.setP1(QPoint(x, y));

            if (sscanf(argv[++i], "%d", &x) != 1 ||
                    sscanf(argv[++i], "%d", &y) != 1)
            {
                code = ERROR_VALUE;
                continue;
            }

            line.setP2(QPoint(x, y));

            controller.drawLine(line, alg, color);
        }
        else if (command == "draw-spectrum")
        {
            int radius, step;

            if (sscanf(argv[++i], "%d", &radius) != 1 ||
                    sscanf(argv[++i], "%d", &step) != 1)
            {
                code = ERROR_VALUE;
                continue;
            }

            spectrum_t spect = {radius, step};

            controller.drawSpectrum(spect, alg, color);
        }
        else
            code = ERROR_COMMAND;
    }

    if (code)
    {
        errors_handler(code);
        return code;
    }

    image->save(filename.c_str(), "JPEG");

    return 0;
}
