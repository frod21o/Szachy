#include "figure.h"

Figure::Figure(Figure *(*board)[8][8], int color, QPoint position):
    color(color), position(position), board(board)
{

}

Figure::~Figure()
{

}

void Figure::diagonal_move()
{
    pinningDirections[1] = 1;
    int x = position.x()+1;
    int y = position.y()+1;
    if(isPinned == 0 || isPinned == 3)
    {
        while(x<8 && y<8 && (*board)[x][y]->get_color() != this->color)
        {
            poss_moves.push_back({x,y});
            if((*board)[x][y]->get_type() !="empty") x = 8;
            x++, y++;
        }
        x = position.x()-1;
        y = position.y()-1;
        while(x>=0 && y>=0 && (*board)[x][y]->get_color() != this->color)
        {
            poss_moves.push_back({x,y});
            if((*board)[x][y]->get_type() !="empty") x = -1;
            x--, y--;
        }
    }
    if(isPinned == 0 || isPinned == 4)
    {
        x = position.x()-1;
        y = position.y()+1;
        while(x>=0 && y<8 && (*board)[x][y]->get_color() != this->color)
        {
            poss_moves.push_back({x,y});
            if((*board)[x][y]->get_type() !="empty") x = -1;
            x--, y++;
        }
        x = position.x()+1;
        y = position.y()-1;
        while(x<8 && y>=0 && (*board)[x][y]->get_color() != this->color)
        {
            poss_moves.push_back({x,y});
            if((*board)[x][y]->get_type() !="empty") x = 8;
            x++, y--;
        }
    }
}

void Figure::hv_move()
{
    pinningDirections[0]=1;
    if(isPinned == 0 || isPinned == 2)
    {
        for(int x = position.rx()-1; x>=0;x--)
        {
            if((*board)[x][position.ry()]->get_color() != this->color)
                poss_moves.push_back({x, position.ry()});
            if((*board)[x][position.ry()]->get_type() != "empty")
                x = -1;
        }
        for(int x = position.rx()+1; x<=7;x++)
        {
            if((*board)[x][position.ry()]->get_color() != this->color)
                poss_moves.push_back({x, position.ry()});
            if((*board)[x][position.ry()]->get_type() != "empty")
                x = 8;
        }
    }
    if(isPinned == 0 || isPinned == 1)
    {
        for(int y = position.ry()-1; y>=0;y--)
        {
            if((*board)[position.rx()][y]->get_color() != this->color)
                poss_moves.push_back({position.rx(), y});
            if((*board)[position.rx()][y]->get_type() != "empty")
                y = -1;
        }
        for(int y = position.ry()+1; y<=7;y++)
        {
            if((*board)[position.rx()][y]->get_color() != this->color)
                poss_moves.push_back({position.rx(), y});
            if((*board)[position.rx()][y]->get_type() != "empty")
                y = 8;
        }
    }
}

void Figure::diagonal_attack()
{
    int x = position.x()+1;
    int y = position.y()+1;
    while(x<8 && y<8)
    {
        (*board)[x][y]->under_attack(color);
        if((*board)[x][y]->get_type() =="king" && (*board)[x][y]->get_color() != this->color)
            i_see_king =1;
        else if((*board)[x][y]->get_type() !="empty") x = 8;
        x++, y++;
    }
    x = position.x()-1;
    y = position.y()+1;
    while(x>=0 && y<8)
    {
        (*board)[x][y]->under_attack(color);
        if((*board)[x][y]->get_type() =="king" && (*board)[x][y]->get_color() != this->color)
            i_see_king =1;
        else if((*board)[x][y]->get_type() !="empty") x = -1;
        x--, y++;
    }
    x = position.x()-1;
    y = position.y()-1;
    while(x>=0 && y>=0)
    {
        (*board)[x][y]->under_attack(color);
        if((*board)[x][y]->get_type() =="king" && (*board)[x][y]->get_color() != this->color)
            i_see_king =1;
        else if((*board)[x][y]->get_type() !="empty") x = -1;
        x--, y--;
    }
    x = position.x()+1;
    y = position.y()-1;
    while(x<8 && y>=0)
    {
        (*board)[x][y]->under_attack(color);
        if((*board)[x][y]->get_type() =="king" && (*board)[x][y]->get_color() != this->color)
            i_see_king =1;
        else if((*board)[x][y]->get_type() !="empty") x = 8;
        x++, y--;
    }
}

void Figure::hv_attack()
{
    for(int x = position.rx()-1; x>=0;x--)
    {
        (*board)[x][position.ry()]->under_attack(color);
        if((*board)[x][position.ry()]->get_type() =="king" && (*board)[x][position.ry()]->get_color() != this->color)
            i_see_king = 1;
        else if((*board)[x][position.ry()]->get_type() != "empty")
            x = -1;
    }
    for(int x = position.rx()+1; x<=7;x++)
    {
        (*board)[x][position.ry()]->under_attack(color);
        if((*board)[x][position.ry()]->get_type() =="king" && (*board)[x][position.ry()]->get_color() != this->color)
            i_see_king = 1;
        else if((*board)[x][position.ry()]->get_type() != "empty")
            x = 8;
    }
    for(int y = position.ry()-1; y>=0;y--)
    {
        (*board)[position.rx()][y]->under_attack(color);
        if((*board)[position.rx()][y]->get_type() =="king" && (*board)[position.rx()][y]->get_color() != this->color)
            i_see_king = 1;
        else if((*board)[position.rx()][y]->get_type() != "empty")
            y = -1;
    }
    for(int y = position.ry()+1; y<=7;y++)
    {
        (*board)[position.rx()][y]->under_attack(color);
        if(((*board)[position.rx()][y]->get_type() =="king" && (*board)[position.rx()][y]->get_color() != this->color))
            i_see_king = 1;
        else if((*board)[position.rx()][y]->get_type() != "empty")
            y = 8;
    }
}

void Figure::erease_variables()
{
    isAttacked[0] = 0;
    isAttacked[1] = 0;
    isPinned = 0;
    i_see_king=0;
}

void Figure::attack()
{
    for(qsizetype i =0; i<poss_moves.size() ; i++)
    {
        (*board)[poss_moves[i].rx()][poss_moves[i].ry()]->under_attack(color);
    }
}

void Figure::next_turn()
{
    get_moves();
    attack();
}

void Figure::move(QPoint target)
{
    position = target;
}

void Figure::filter_moves(QList<QPoint> &filter_list)
{
    for(int move_id=0; move_id<poss_moves.size();move_id++)
    {
        bool found=0;
        for(int test=0;test<filter_list.size();test++)
        {
            if(filter_list[test] == poss_moves[move_id])
            {
                found=1;
                test=filter_list.size();
            }
        }
        if(!found)
        {
            poss_moves.removeAt(move_id);
            move_id--;
        }
    }
}
