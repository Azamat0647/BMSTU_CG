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
    Controller(QImage *image, QStandardItemModel *pointsTableModel);
    ~Controller();

    QImage *image()
    {
        return _image;
    };
    void setPointsModel(QStandardItemModel *pointsTableModel);
    void setSeedPoint(const QPoint &point);
    void resetSeedPoint();

    void addPoint(const QPoint &point);
    void removeLastPoint();

    void closePolygon();
    QPoint lastPoint();

    bool pointsIsEmpty()
    {
        return points.isEmpty();
    };
    int pointsCount()
    {
        return points.size();
    };

    void fill(const QColor &color, unsigned int delay);

    void clearScreen();

  signals:
    void imageChanged();
    void seedPointChanged(const QPoint &point);

  private:
    QImage *_image;
    QStandardItemModel *pointsTable;
    std::unique_ptr<QPoint> seedPoint{nullptr};
    QList<QPoint> points;

    void removeLastRowFormTable();
    void addRowToTable(QString x, QString y);
    void pointsTableInit();
    void clearPointsTable();
};

#endif // CONTROLLER_H
