#ifndef SPECIALCHECKER_H
#define SPECIALCHECKER_H

#include "figure.h"

class SpecialChecker : public Figure
{
public:
    SpecialChecker(Figure *(*board)[8][8], int color, QPoint position);
    ~SpecialChecker();

    void get_moves();
    void next_turn();

protected:
    QList<QPoint> directions;
};

#endif // SPECIALCHECKER_H
