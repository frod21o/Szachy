#include "rook.h"

Rook::Rook(Figure *(*board)[8][8], int color, QPoint position)
    :Figure(board, color, position)
{
    type = "rook";
    if(color)
        image.load(":/Figures/white_rook.png");
    else
        image.load(":/Figures/black_rook.png");

    move_info=1;
}

Rook::~Rook()
{

}

void Rook::get_moves()
{
    poss_moves.clear();
    hv_move();
}

void Rook::attack()
{
    hv_attack();
}

void Rook::move(QPoint target)
{
    position = target;
    move_info =0;
}
