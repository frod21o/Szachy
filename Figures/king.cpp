#include "king.h"

King::King(Figure *(*board)[8][8], int color, QPoint position)
    :Figure(board, color, position)
{
    type = "king";
    if(color)
        image.load(":/Figures/white_king.png");
    else
        image.load(":/Figures/black_king.png");

    move_info =1;
}

King::~King()
{

}

void King::get_moves()
{
    poss_moves.clear();

    QPoint directions[8] = {
        {0,1}, {0,-1},
        {-1,1}, {-1,-1},
        {1,0}, {-1,0},
        {1,1}, {1,-1},
    };

    for(int i = 0; i<8;i++)
    {
        QPoint potencial_move = position + directions[i];

        if(potencial_move.rx()<=7 && potencial_move.rx()>=0 && potencial_move.ry()<=7 && potencial_move.ry()>=0)
            if((*board)[potencial_move.rx()][potencial_move.ry()]->get_color() != this->color && (*board)[potencial_move.rx()][potencial_move.ry()]->get_isAttacked(!color)==0)
                poss_moves.push_back(potencial_move);
    }
    //// CASTLE
    if(!isAttacked[!color] && move_info)
    {
        //// LONG
        if((*board)[0][position.y()]->get_move_info() && (*board)[0][position.y()]->get_color() == this->color)
        {
            bool possible = 1;
            for(int i=-1;i>=-2;i--)
                if((*board)[position.x()+i][position.y()]->get_type() != "empty" || (*board)[position.x()+i][position.y()]->get_isAttacked(!color))
                    possible = 0;
            if((*board)[position.x()-3][position.y()]->get_type() != "empty")
                possible = 0;

            if(possible)
                poss_moves.push_back({position.x()-2,position.y()});
        }
        //// SHORT
        if((*board)[7][position.y()]->get_move_info() && (*board)[7][position.y()]->get_color() == this->color)
        {
            bool possible = 1;
            for(int i=1;i<=2;i++)
                if((*board)[position.x()+i][position.y()]->get_type() != "empty" || (*board)[position.x()+i][position.y()]->get_isAttacked(!color))
                    possible = 0;

            if(possible)
                poss_moves.push_back({position.x()+2,position.y()});
        }
    }
}

void King::attack()
{
    QPoint directions[8] = {
        {0,1}, {0,-1},
        {-1,1}, {-1,-1},
        {1,0}, {-1,0},
        {1,1}, {1,-1},
    };

    for(int i = 0; i<8;i++)
    {
        QPoint potencial_move = position + directions[i];
        if(potencial_move.rx()<=7 && potencial_move.rx()>=0 && potencial_move.ry()<=7 && potencial_move.ry()>=0)
            (*board)[potencial_move.rx()][potencial_move.ry()]->under_attack(color);
    }
}

void King::move(QPoint target)
{
    position = target;
    move_info =0;
}

void King::pin_and_check()
{

    QPoint directions[8] = {
        {0,1}, {0,-1},
        {-1,1}, {-1,-1},
        {1,0}, {-1,0},
        {1,1}, {1,-1},
    };
    for(int i=0;i<8;i++)
    {
        int figures_counter=0;
        QPoint current_position = position + directions[i];
        QPoint figures_met[2];
        while(current_position.rx()<=7 && current_position.rx()>=0 && current_position.ry()<=7 && current_position.ry()>=0 &&figures_counter<2)
        {
            if((*board)[current_position.rx()][current_position.ry()]->get_type() != "empty")
            {
                figures_met[figures_counter] = (*board)[current_position.rx()][current_position.ry()]->get_position();
                figures_counter++;
            }
            current_position+=directions[i];
        }

        if(figures_counter >0)
        {
            if((*board)[figures_met[0].rx()][figures_met[0].ry()]->get_color() != this->color)
            {
                if((*board)[figures_met[0].rx()][figures_met[0].ry()]->get_i_see_king())
                    check_position = figures_met[0];
            }
            else
            {
                if(figures_counter == 2)
                {
                    bool pinIndex = (convert_direction_PtoV(directions[i])-1)/2;
                    if((*board)[figures_met[1].rx()][figures_met[1].ry()]->get_color() != this->color && (*board)[figures_met[1].rx()][figures_met[1].ry()]->get_pinningDirections(pinIndex))
                    {
                        (*board)[figures_met[0].rx()][figures_met[0].ry()]->pin(convert_direction_PtoV(directions[i]));
                    }
                }
            }
        }
    }
}

int King::convert_direction_PtoV(QPoint direction_point)
{
    int direction_value=0;
    if(direction_point.rx() == 0) direction_value = 1;
    else if(direction_point.ry() == 0) direction_value = 2;
    else if(direction_point.rx() * direction_point.ry() > 0) direction_value = 3;
    else if(direction_point.rx() * direction_point.ry() < 0) direction_value = 4;

    return direction_value;
}
