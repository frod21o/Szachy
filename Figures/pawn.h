#ifndef PAWN_H
#define PAWN_H

#include "figure.h"

class Pawn: public Figure
{
public:
    Pawn(Figure *(*board)[8][8], int color, QPoint position);
    ~Pawn();

    void get_moves();
    void attack();
};

#endif // PAWN_H
