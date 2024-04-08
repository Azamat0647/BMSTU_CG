#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "cross.h"

class Rhombus : public Cross
{
public:
    using Cross::Cross;
    void draw(QChart *chart, const QPen &pen);
};

#endif // RHOMBUS_H
