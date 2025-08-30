#ifndef CHECKERSBOARD_H
#define CHECKERSBOARD_H

#include "boarddata.h"

#include "Figures/checkerspiece.h"
#include "Figures/checkersqueen.h"

class CheckersBoard : public BoardData
{
public:
    CheckersBoard();
    ~CheckersBoard();
private:
    void set_new_board();
    void update_board();
    int move(Figure* figure, QPoint new_position); // 0 not possible move, 1 moved, 2 pawn is promoting

    void after_capture(QPoint clicked_cell);

    void next_turn();
public:
    void clicked(QPoint clicked_cell);
};

#endif // CHECKERSBOARD_H
