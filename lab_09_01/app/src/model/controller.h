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
    Controller(QImage *image, QStandardItemModel *polygonTableModel,
               QStandardItemModel *cutterTableModel);
    ~Controller();

    QImage *image()
    {
        return _image;
    };
    void setPolygonModel(QStandardItemModel *polygonTableModel);
    void setCutterModel(QStandardItemModel *cutterTableModel);

    void closeCutter();
    void closePolygon();

    void resetCutter();

    void addPolygonPoint(const QPoint &point);
    void addCutterPoint(const QPoint &point);

    QPoint lastCutterPoint() { return cutterPoints.last(); };
    QPoint lastPolygonPoint() { return polygonPoints.last(); };

    void removeLastPolygonPoint();
    void removeLastCutterPoint();

    QColor cutterColor() { return _cutterColor; };
    QColor polygonColor() { return _polygonColor; };
    QColor resColor() { return _resColor; };

    QColor setCutterColor(const QColor &color) { return _cutterColor = color; };
    QColor setPolygonColor(const QColor &color) { return _polygonColor = color; };
    QColor setResColor(const QColor &color) { return _resColor = color; };

    bool polygonPointsIsEmpty() { return polygonPoints.isEmpty(); };
    bool cutterPointsIsEmpty() { return cutterPoints.isEmpty(); };

    int cutterPointsCount() { return cutterPoints.size(); };
    int polygonPointsCount() { return polygonPoints.size(); };

    void cutOff();

    void clearScreen();

  signals:
    void imageChanged();

  private:
    QImage *_image;
    QStandardItemModel *polygonTable;
    QStandardItemModel *cutterTable;

    QScopedPointer<Polygon> cutter{nullptr};
    QList<Polygon> polygons;

    QVector<QPoint> cutterPoints;
    QVector<QPoint> polygonPoints;

    QColor _cutterColor;
    QColor _polygonColor;
    QColor _resColor;

    static void removeLastRowFormTable(QStandardItemModel *model);
    static void addRowToTable(QString x, QString y,
                              QStandardItemModel *model);
    void initTable(QStandardItemModel *model);

    void clearTable(QStandardItemModel *model);

    void redrawPolygons();
};

#endif // CONTROLLER_H
