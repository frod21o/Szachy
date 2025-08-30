#ifndef QUEEN_H
#define QUEEN_H

#include "figure.h"

class Queen : public Figure
{
public:
    Queen(Figure *(*board)[8][8], int color, QPoint position);
    ~Queen();

    void get_moves();
    void attack();
};

#endif // QUEEN_H
