#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "drawer.h"
#include <QtWidgets>

#include <stdexcept>


class Controller : public QObject
{
    Q_OBJECT
  public:
    explicit Controller(QImage *image);
    Controller();
    Controller(QImage *image, QStandardItemModel *linesTableModel);
    ~Controller();

    QImage *image()
    {
        return _image;
    };
    void setLinesModel(QStandardItemModel *linesTableModel);
    void setCutterRect(const QRect &rect);
    void resetCutterRect();

    void addLine(const QLine &line);
    void removeLastLine();

    QColor cutterColor() { return _cutterColor; };
    QColor lineColor() { return _lineColor; };
    QColor resColor() { return _resColor; };

    QColor setCutterColor(const QColor &color) { return _cutterColor = color; };
    QColor setLineColor(const QColor &color) { return _lineColor = color; };
    QColor setResColor(const QColor &color) { return _resColor = color; };

    bool linesIsEmpty() { return lines.isEmpty(); };
    int linesCount() { return lines.size(); };

    void cutOff();

    void clearScreen();

  signals:
    void imageChanged();
    void cutterRectSetted(const QRect &rect);

  private:
    QImage *_image;
    QStandardItemModel *linesTable;
    std::unique_ptr<QRect> cutterRect{nullptr};
    QList<QLine> lines;

    QColor _cutterColor;
    QColor _lineColor;
    QColor _resColor;

    void removeLastRowFormTable();
    void addRowToTable(QString x, QString y);
    void linesTableInit();
    void clearLinesTable();
    void redrawLines();
};

#endif // CONTROLLER_H
