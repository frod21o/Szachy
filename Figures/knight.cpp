#include "knight.h"

Knight::Knight(Figure *(*board)[8][8], int color, QPoint position)
    :Figure(board, color, position)
{
    type = "knight";
    if(color)
        image.load(":/Figures/white_knight.png");
    else
        image.load(":/Figures/black_knight.png");
}

Knight::~Knight()
{

}

void Knight::get_moves()
{
    poss_moves.clear();

    if(isPinned ==0)
    {
        QPoint directions[8] = {
            {2,1}, {2,-1},
            {-2,1}, {-2,-1},
            {1,2}, {-1,2},
            {1,-2}, {-1,-2},
        };

        for(int i = 0; i<8;i++)
        {
            QPoint potencial_move = position + directions[i];

            if(potencial_move.rx()<=7 && potencial_move.rx()>=0 && potencial_move.ry()<=7 && potencial_move.ry()>=0)
            {
                if((*board)[potencial_move.rx()][potencial_move.ry()]->get_color() != this->color)
                {
                    poss_moves.push_back(potencial_move);
                    if((*board)[potencial_move.rx()][potencial_move.ry()]->get_type() == "king")
                        (*board)[potencial_move.rx()][potencial_move.ry()]->add_check(position);
                }
            }
        }
    }
}

void Knight::attack()
{
    QPoint directions[8] = {
        {2,1}, {2,-1},
        {-2,1}, {-2,-1},
        {1,2}, {-1,2},
        {1,-2}, {-1,-2},
    };

    for(int i = 0; i<8;i++)
    {
        QPoint potencial_move = position + directions[i];
        if(potencial_move.rx()<=7 && potencial_move.rx()>=0 && potencial_move.ry()<=7 && potencial_move.ry()>=0)
            (*board)[potencial_move.rx()][potencial_move.ry()]->under_attack(this->color);
    }
}

