#ifndef MOVESNAPSHOT_H
#define MOVESNAPSHOT_H

#include "Figures/figure.h"

class MoveSnapshot
{
public:
    MoveSnapshot();
    QList<int> orderOfActions = {}; //1xx set, 2xx vanished, 3xx moved, xx index
    QList<Figure*> set_figures = {};
    QList<Figure*> vanished_figures = {};
    QList<QPoint> moved_figures[2] ={{},{}};
    QList<int> move_info[2] ={{},{}};
    bool stored = 0;

    void clear();
    bool isEmpty();
    bool isThere_move(QPoint old_position, QPoint new_position, int info1, int info2);
};

#endif // MOVESNAPSHOT_H
