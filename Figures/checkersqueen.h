#ifndef CHECKERSQUEEN_H
#define CHECKERSQUEEN_H

#include "checkerspiece.h"

class CheckersQueen : public CheckersPiece
{
public:
    CheckersQueen(Figure *(*board)[8][8], int color, QPoint position);
    ~CheckersQueen();

    void get_moves();

    static bool long_queen_move;
};

#endif // CHECKERSQUEEN_H
