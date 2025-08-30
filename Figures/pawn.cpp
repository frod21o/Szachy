#include "pawn.h"


Pawn::Pawn(Figure *(*board)[8][8], int color, QPoint position)
    :Figure(board, color, position)
{
    type = "pawn";
    if(color)
        image.load(":/Figures/white_pawn.png");
    else
        image.load(":/Figures/black_pawn.png");
}

Pawn::~Pawn()
{

}

void Pawn::get_moves()
{
    poss_moves.clear();
    int direction = !color*2 -1;

    int x = position.rx();
    int y = position.ry() + direction;
    if(y >= 0 && y <= 7)
    {
        if((*board)[x][y]->get_type() == "empty" && (isPinned == 0 || isPinned == 1))
            poss_moves.push_back({x,y});

        if(isPinned == 0 || (isPinned == 4 && !color) || (isPinned == 3 && color))
        {
            if(x>0 && (*board)[x-1][y]->get_type() != "empty" && (*board)[x-1][y]->get_color() != color)
                poss_moves.push_back({x-1,y});
            if(move_info==-1)
                poss_moves.push_back({x-1,y});
        }

        if(isPinned == 0 || (isPinned == 3 && !color) || (isPinned == 4 && color))
        {
            if(x<7 && (*board)[x+1][y]->get_type() != "empty" && (*board)[x+1][y]->get_color() != color)
                poss_moves.push_back({x+1,y});
            if(move_info==1)
                poss_moves.push_back({x+1,y});
        }
    }

    if(((color && y == 5 )||(!color && y == 2)) && (isPinned == 0 || isPinned == 1))
        if((*board)[x][y]->get_type() == "empty" && (*board)[x][y+direction]->get_type() == "empty")
            poss_moves.push_back({x,y + direction});
}

void Pawn::attack()
{
    int direction = !color*2 -1;

    int x = position.rx();
    int y = position.ry() + direction;
    if(y >= 0 && y <= 7)
    {
        if(x>0)
        {
            (*board)[x-1][y]->under_attack(this->color);
            if((*board)[x-1][y]->get_type() == "king" && (*board)[x-1][y]->get_color() != this->color)
                i_see_king=1;
        }
        if(x<7)
        {
            (*board)[x+1][y]->under_attack(this->color);
            if((*board)[x+1][y]->get_type() == "king" && (*board)[x+1][y]->get_color() != this->color)
                i_see_king=1;
        }
    }
}
