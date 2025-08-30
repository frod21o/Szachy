#include "checkerspiece.h"

bool CheckersPiece::back_take = 0;
bool CheckersPiece::take_obligation =0;
bool CheckersPiece::we_take[2] = {0,0};

CheckersPiece::CheckersPiece(Figure *(*board)[8][8], int color, QPoint position)
    :Figure(board, color, position)
{
    type = "checkerspiece";
    if(color)
        image.load(":/Figures/white_checkerspiece.png");
    else
        image.load(":/Figures/black_checkerspiece.png");

}

CheckersPiece::~CheckersPiece()
{

}

void CheckersPiece::get_moves()
{
    poss_moves.clear();
    int direction = !color*2 -1;

    int x = position.rx();
    int y = position.ry() + direction;

    if(y >= 0 && y <= 7)
    {
        if((!take_obligation || !we_take[color]) && !move_info)
        {
            if(x>0 && (*board)[x-1][y]->get_type() == "empty")
                poss_moves.push_back({x-1,y});

            if(x<7 && (*board)[x+1][y]->get_type() == "empty")
                poss_moves.push_back({x+1,y});
        }
    }

    int take_check = poss_moves.length();
    if(y >= 1 && y <= 6)
    {
        if(x>1 && (*board)[x-1][y]->get_type() != "empty" && (*board)[x-1][y]->get_color() != color && (*board)[x-2][y+direction]->get_type() == "empty")
            poss_moves.push_back({x-2,y+direction});

        if(x<6 && (*board)[x+1][y]->get_type() != "empty" && (*board)[x+1][y]->get_color() != color && (*board)[x+2][y+direction]->get_type() == "empty")
            poss_moves.push_back({x+2,y+direction});
    }

    y -= 2*direction;
    if(back_take && y >= 1 && y <= 6)
    {
        if(x>1 && (*board)[x-1][y]->get_type() != "empty" && (*board)[x-1][y]->get_color() != color && (*board)[x-2][y-direction]->get_type() == "empty")
            poss_moves.push_back({x-2,y-direction});

        if(x<6 && (*board)[x+1][y]->get_type() != "empty" && (*board)[x+1][y]->get_color() != color && (*board)[x+2][y-direction]->get_type() == "empty")
            poss_moves.push_back({x+2,y-direction});
    }
    if(take_check<poss_moves.length())
        we_take[color] = 1;
    if(move_info && poss_moves.size() && !take_obligation)
        poss_moves.push_back(position);
}
