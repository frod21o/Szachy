#ifndef BISHOP_H
#define BISHOP_H

#include "figure.h"

class Bishop : public Figure
{
public:
    Bishop(Figure *(*board)[8][8], int color, QPoint position);
    ~Bishop();

    void get_moves();
    void attack();
};

#endif // BISHOP_H
