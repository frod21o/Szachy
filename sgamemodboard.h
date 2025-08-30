#ifndef SGAMEMODBOARD_H
#define SGAMEMODBOARD_H

#include "boarddata.h"

#include "Figures/pawn.h"
#include "Figures/rook.h"
#include "Figures/bishop.h"
#include "Figures/queen.h"
#include "Figures/knight.h"
#include "Figures/king.h"

#include "Figures/specialchecker.h"
#include "Figures/specialqueen.h"

class SGamemodBoard : public BoardData
{
public:
    SGamemodBoard();
    ~SGamemodBoard();

private:
    void set_new_board();
    void update_board();
    int move(Figure* figure, QPoint new_position); // 0 not possible move, 1 moved, 2 pawn is promoting

    void after_capture(QPoint clicked_cell);
public:

    void clicked(QPoint clicked_cell);

    static bool checkers_color;
};

#endif // SGAMEMODBOARD_H
