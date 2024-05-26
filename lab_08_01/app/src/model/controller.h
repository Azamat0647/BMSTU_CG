#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "drawer.h"
#include "polygon.h"
#include <QtWidgets>

#include <stdexcept>


class Controller : public QObject
{
    Q_OBJECT
  public:
    explicit Controller(QImage *image);
    Controller();
    Controller(QImage *image, QStandardItemModel *linesTableModel,
               QStandardItemModel *cutterTableModel);
    ~Controller();

    QImage *image()
    {
        return _image;
    };
    void setLinesModel(QStandardItemModel *linesTableModel);
    void setCutterModel(QStandardItemModel *cutterTableModel);

    void closeCutterPolygon();
    void resetCutterPolygon();

    void addLine(const QLine &line);
    void addCutterPoint(const QPoint &point);
    QPoint lastCutterPoint();

    void removeLastLine();
    void removeLastCutterPoint();

    QColor cutterColor() { return _cutterColor; };
    QColor lineColor() { return _lineColor; };
    QColor resColor() { return _resColor; };

    QColor setCutterColor(const QColor &color) { return _cutterColor = color; };
    QColor setLineColor(const QColor &color) { return _lineColor = color; };
    QColor setResColor(const QColor &color) { return _resColor = color; };

    bool linesIsEmpty() { return lines.isEmpty(); };
    bool pointsIsEmpty() { return cutterPoints.isEmpty(); };
    int pointsCount() { return cutterPoints.size(); };

    void cutOff();

    void clearScreen();

  signals:
    void imageChanged();
    void cutterSetted(const Polygon &polygon);

  private:
    QImage *_image;
    QStandardItemModel *linesTable;
    QStandardItemModel *cutterTable;

    std::unique_ptr<Polygon> cutterPolygon{nullptr};
    QVector<QPoint> cutterPoints;
    QVector<QLine> lines;

    QColor _cutterColor;
    QColor _lineColor;
    QColor _resColor;

    static void removeLastRowFormTable(QStandardItemModel *model);
    static void addRowToTable(QString x, QString y,
                              QStandardItemModel *model);
    void linesTableInit();
    void cutterTableInit();

    void clearTable(QStandardItemModel *model);

    void redrawLines();
};

#endif // CONTROLLER_H
