#include "specialchecker.h"

SpecialChecker::SpecialChecker(Figure *(*board)[8][8], int color, QPoint position)
    :Figure(board, color, position)
{
    type = "specialchecker";
    if(color)
        image.load(":/Figures/white_checkerspiece.png");
    else
        image.load(":/Figures/black_checkerspiece.png");

    int ydir = 2*!color -1;
    directions.append(
                {
                    {0, ydir}, {-1,ydir}, {1,ydir},
                    {-1,0}, {1,0}
                }
                );
}

SpecialChecker::~SpecialChecker()
{

}

void SpecialChecker::get_moves()
{
    poss_moves.clear();
    for(int i = 0; i<directions.size(); i++)
    {
        QPoint new_position = position + directions[i];
        if(new_position.x() <0) new_position.rx() +=8;
        if(new_position.x() >7) new_position.rx() -=8;
        if(new_position.y() <0) new_position.ry() +=8;
        if(new_position.y() >7) new_position.ry() -=8;

        if((*board)[new_position.x()][new_position.y()]->get_type() == "empty")
        {
            if(!move_info)
                poss_moves.push_back(new_position);
        }
        else if((*board)[new_position.x()][new_position.y()]->get_color() != this->color)
        {
            new_position = new_position + directions[i];
            if(new_position.x() <0) new_position.rx() +=8;
            if(new_position.x() >7) new_position.rx() -=8;
            if(new_position.y() <0) new_position.ry() +=8;
            if(new_position.y() >7) new_position.ry() -=8;

            if((*board)[new_position.x()][new_position.y()]->get_type() == "empty")
                poss_moves.push_back(new_position);
        }
    }
    if(move_info && poss_moves.size()>0)
        poss_moves.push_back(position);
}

void SpecialChecker::next_turn()
{
    move_info = 0;
    get_moves();
}
