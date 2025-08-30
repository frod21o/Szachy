#ifndef SPECIALQUEEN_H
#define SPECIALQUEEN_H

#include <specialchecker.h>

class SpecialQueen : public SpecialChecker
{
public:
    SpecialQueen(Figure *(*board)[8][8], int color, QPoint position);
    ~SpecialQueen();
};

#endif // SPECIALQUEEN_H
