#include "queen.h"

Queen::Queen(Figure *(*board)[8][8], int color, QPoint position)
    :Figure(board, color, position)
{
    type = "queen";
    if(color)
        image.load(":/Figures/white_queen.png");
    else
        image.load(":/Figures/black_queen.png");
}

Queen::~Queen()
{

}

void Queen::get_moves()
{
    poss_moves.clear();
    diagonal_move();
    hv_move();
}

void Queen::attack()
{
    diagonal_attack();
    hv_attack();
}
