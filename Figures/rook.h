#ifndef ROOK_H
#define ROOK_H

#include "figure.h"

class Rook: public Figure
{
public:
    Rook(Figure *(*board)[8][8], int color, QPoint position);
    ~Rook();

    void get_moves();
    void attack();
    void move(QPoint target);
};

#endif // ROOK_H
