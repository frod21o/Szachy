#ifndef EMPTYSPACE_H
#define EMPTYSPACE_H

#include "figure.h"

class EmptySpace : public Figure
{
public:
    EmptySpace(Figure *(*board)[8][8], QPoint position);
    ~EmptySpace();

    inline void get_moves() {};
    inline void attack() {};
};

#endif // EMPTYSPACE_H
