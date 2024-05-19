#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "polygon.h"
#include "drawer.h"
#include <QtWidgets>


class Controller : public QObject
{
    Q_OBJECT
  public:
    explicit Controller(QImage *image);
    Controller();
    Controller(QImage *image, QStandardItemModel *pointsTableModel);
    ~Controller();

    QImage *image()
    {
        return _image;
    };
    void setPointsModel(QStandardItemModel *pointsTableModel);

    void addPoint(const QPoint &point);
    void removeLastPoint();
    void closePolygon();
    QPoint lastPoint();
    bool pointsIsEmpty() { return curPolygon.isEmpty(); };
    int pointsCount() { return curPolygon.size(); };

    void fill(const QColor &color, unsigned int delay);

    void clearScreen();

  signals:
    void imageChanged();

  private:
    QImage *_image;
    QStandardItemModel *pointsTable;
    Polygon curPolygon;
    QList<Polygon> polygons;

    void fillLine(const QPoint &inters_point, int partition, Drawer &drawer, int delay);

    void removeLastRowFormTable();
    void addRowToTable(QString x, QString y);
    void pointsTableInit();
    void clearPointsTable();
};

#endif // CONTROLLER_H
