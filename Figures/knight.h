#ifndef KNIGHT_H
#define KNIGHT_H

#include "figure.h"

class Knight : public Figure
{
public:
    Knight(Figure *(*board)[8][8], int color, QPoint position);
    ~Knight();

    void get_moves();
    void attack();
};

#endif // KNIGHT_H
