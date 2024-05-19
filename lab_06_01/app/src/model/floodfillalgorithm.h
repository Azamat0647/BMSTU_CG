#ifndef FLOODFILLALGORITHM_H
#define FLOODFILLALGORITHM_H

#include "drawer.h"

class FloodFillAlgorithm : public QObject
{
    Q_OBJECT
  public:
    explicit FloodFillAlgorithm(Drawer &drawer);
    explicit FloodFillAlgorithm(Drawer &drawer, const QColor &borderColor);

    void fill(const QPoint &seedPoint, unsigned int delay);

  private:
    Drawer &_drawer;
    QColor _borderColor{0, 0, 0};
    QColor _fillColor;

    void findNewSeedPoints(int left, int right, int y, QStack<QPoint> &stack);

    void sleep(unsigned int delay);

    inline bool isFilled(int x, int y);
    inline bool isBorder(int x, int y);

  signals:
    void screenUpdated();
};

#endif // FLOODFILLALGORITHM_H
