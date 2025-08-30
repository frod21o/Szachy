#ifndef CHECKERSPIECE_H
#define CHECKERSPIECE_H

#include "figure.h"

class CheckersPiece : public Figure
{
public:
    CheckersPiece(Figure *(*board)[8][8], int color, QPoint position);
    ~CheckersPiece();

    virtual void get_moves();


    static bool back_take;
    static bool take_obligation;

    static bool we_take[2];
};

#endif // CHECKERSPIECE_H
