#include "bishop.h"

Bishop::Bishop(Figure *(*board)[8][8], int color, QPoint position)
    :Figure(board, color, position)
{
    type = "bishop";
    if(color)
        image.load(":/Figures/white_bishop.png");
    else
        image.load(":/Figures/black_bishop.png");
}

Bishop::~Bishop()
{

}

void Bishop::get_moves()
{
    poss_moves.clear();
    diagonal_move();
}

void Bishop::attack()
{
    diagonal_attack();
}
