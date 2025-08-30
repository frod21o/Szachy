#include "checkersqueen.h"

bool CheckersQueen::long_queen_move=0;

CheckersQueen::CheckersQueen(Figure *(*board)[8][8], int color, QPoint position)
    :CheckersPiece(board, color, position)
{
    type = "checkersqueen";
    if(color)
        image.load(":/Figures/white_checkersqueen.png");
    else
        image.load(":/Figures/black_checkersqueen.png");
}

CheckersQueen::~CheckersQueen()
{

}

void CheckersQueen::get_moves()
{
    poss_moves.clear();

    if(long_queen_move)
    {
        QPoint directions[4] = {
            {1,1},{1,-1},
            {-1,1},{-1,-1}
        };

        for(int dir_num = 0; dir_num<4;dir_num++)
        {
            bool break_loop = 0;
            int poss_num = 1;
            while(!break_loop)
            {
                QPoint curr_poss = position + directions[dir_num] * poss_num;
                if(curr_poss.x()>=0 && curr_poss.x()<=7 && curr_poss.y()>=0 && curr_poss.y()<=7)
                {
                    if((*board)[curr_poss.x()][curr_poss.y()]->get_type() == "empty")
                    {
                        if((!take_obligation || !we_take[color]) && !move_info)
                            poss_moves.push_back(curr_poss);
                    }
                    else
                    {
                        if((*board)[curr_poss.x()][curr_poss.y()]->get_color() != this->color)
                        {
                            QPoint next_poss = curr_poss + directions[dir_num];
                            if(next_poss.x()>=0 && next_poss.x()<=7 && next_poss.y()>=0 && next_poss.y()<=7 && (*board)[next_poss.x()][next_poss.y()]->get_type() == "empty")
                            {
                                we_take[color] = 1;
                                poss_moves.push_back(next_poss);
                            }
                        }
                        break_loop =1;
                    }
                    poss_num++;
                }
                else break_loop = 1;
            }
        }
    }
    else
    {
        int direction = !color*2 -1;

        int x = position.rx();
        int y = position.ry() - direction;

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
        y+=2*direction;

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
        if(y >= 1 && y <= 6)
        {
            if(x>1 && (*board)[x-1][y]->get_type() != "empty" && (*board)[x-1][y]->get_color() != color && (*board)[x-2][y-direction]->get_type() == "empty")
                poss_moves.push_back({x-2,y-direction});

            if(x<6 && (*board)[x+1][y]->get_type() != "empty" && (*board)[x+1][y]->get_color() != color && (*board)[x+2][y-direction]->get_type() == "empty")
                poss_moves.push_back({x+2,y-direction});
        }
        if(take_check<poss_moves.length())
            we_take[color] = 1;

    }
    if(move_info && poss_moves.size() && !take_obligation)
        poss_moves.push_back(position);
}
