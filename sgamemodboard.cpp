#include "sgamemodboard.h"

bool SGamemodBoard::checkers_color = 1;

SGamemodBoard::SGamemodBoard()
{
    set_new_board();
    update_board();
}

SGamemodBoard::~SGamemodBoard()
{
    delete_board();
}

void SGamemodBoard::set_new_board()
{
    selected_figure = &universal_empty;

    int y = 0;
    int step =1;
    if(!checkers_color)
    {
        y=7;
        step=-1;
    }

    board[0][y] = new Rook(boardPointer, !checkers_color, {0,y});
    board[7][y] = new Rook(boardPointer, !checkers_color, {7,y});

    board[2][y] = new Bishop(boardPointer, !checkers_color, {2,y});
    board[5][y] = new Bishop(boardPointer, !checkers_color, {5,y});

    board[1][y] = new Knight(boardPointer, !checkers_color, {1,y});
    board[6][y] = new Knight(boardPointer, !checkers_color, {6,y});

    board[3][y] = new Queen(boardPointer, !checkers_color, {3,y});

    board[4][y] = new King(boardPointer, !checkers_color, {4, y});

    y+=step;
    for(int i=0;i<8;i++)
        board[i][y] = new Pawn(boardPointer,!checkers_color, {i, y});

    y+=step;
    for(int i=0;i<8;i++)
        board[i][y] = new EmptySpace(boardPointer, {i, y});

    for(int y=3;y<5;y++)
        for(int x=0;x<8;x++)
            board[x][y] = new EmptySpace(boardPointer, {x, y});
    y+=3*step;
    for(int yi=y; yi*step < (y+3*step) *step; yi+=step)
    {
        for(int x=0;x<8;x++)
        {
            if((x+yi)%2)
                board[x][yi] = new SpecialChecker(boardPointer, checkers_color, {x, yi});
            else
                board[x][yi] = new EmptySpace(boardPointer, {x, yi});
        }
    }

    whos_turn = 1;
    game_state = -1;
}

void SGamemodBoard::update_board()
{
    int total_figures = 0;
    bool king = 0;
    for(int x=0;x<8;x++)
    {
        for(int y=0;y<8;y++)
        {
            board[x][y]->next_turn();
            if(board[x][y]->get_color() == whos_turn)
                total_figures++;
            if(board[x][y]->get_type() == "king")
                king =1;
        }
    }
    if(total_figures ==0 || !king)
        game_state = 21;
}

int SGamemodBoard::move(Figure *figure, QPoint new_position)
{
    for(int i=0; i<figure->poss_moves.size();i++)
    {
        if(figure->poss_moves[i] == new_position)
        {
            QPoint old_position = figure->get_position();
            if(old_position == new_position) return 1;
            int old_move_info = figure->get_move_info();

            boardHistory.add_vanishedFig(board[new_position.rx()][new_position.ry()]);

            board[new_position.rx()][new_position.ry()] = figure;
            board[new_position.rx()][new_position.ry()]->move(new_position);
            int new_move_info = board[new_position.rx()][new_position.ry()]->get_move_info();
            board[old_position.rx()][old_position.ry()] = new EmptySpace(boardPointer,old_position);

            boardHistory.add_movedFig(old_position,new_position, old_move_info, new_move_info);

            if(figure->get_type() == "pawn" && (new_position.ry() == 0 || new_position.ry()== 7)) /// PAWN PROMOTION
            {
                game_state = 10 + new_position.x();
                return 3;
            }

            if(figure->get_type() == "king") /// CASTLE
            {
                if(new_position.x() - old_position.x() == 2) /// SHORT
                {
                    delete board[5][new_position.y()];
                    board[5][new_position.y()] = board[7][new_position.y()];
                    board[7][new_position.y()] = new EmptySpace(boardPointer,{7,new_position.y()});
                    old_move_info = board[5][new_position.y()]-> get_move_info();
                    board[5][new_position.y()]->move({5,new_position.y()});
                    new_move_info = board[5][new_position.y()]-> get_move_info();

                    boardHistory.add_movedFig({7,new_position.y()},{5,new_position.y()}, old_move_info, new_move_info);
                }
                if(new_position.x() - old_position.x() == -2) /// LONG
                {
                    delete board[3][new_position.y()];
                    board[3][new_position.y()] = board[0][new_position.y()];
                    board[0][new_position.y()] = new EmptySpace(boardPointer,{0,new_position.y()});
                    old_move_info = board[3][new_position.y()]-> get_move_info();
                    board[3][new_position.y()]->move({3,new_position.y()});
                    new_move_info = board[3][new_position.y()]-> get_move_info();
                    boardHistory.add_movedFig({0,new_position.y()},{3,new_position.y()}, old_move_info, new_move_info);
                }
            }
            if(figure->get_type() == "specialchecker" || figure->get_type() == "specialqueen")
            {
                if(figure->get_type() == "specialchecker")
                {
                    if((figure->get_color() && new_position.y() == 0) || (!figure->get_color() && new_position.y() == 7)
                            || new_position.y() - old_position.y() > 2 || new_position.y() - old_position.y() < -2)
                    {
                        boardHistory.add_vanishedFig(figure);
                        board[new_position.rx()][new_position.ry()] = new SpecialQueen(boardPointer,figure->get_color(), new_position);
                        boardHistory.add_setFig(board[new_position.rx()][new_position.ry()]);
                    }
                }
                QPoint before_new_position = new_position - old_position;
                if(before_new_position.x() <-2) before_new_position.rx() +=8;
                if(before_new_position.x() >2) before_new_position.rx() -=8;
                if(before_new_position.y() <-2) before_new_position.ry() +=8;
                if(before_new_position.y() >2) before_new_position.ry() -=8;

                if(before_new_position.x() != 0) before_new_position.rx() /= abs(before_new_position.x());
                if(before_new_position.y() != 0) before_new_position.ry() /= abs(before_new_position.y());
                before_new_position = new_position - before_new_position;

                if(before_new_position.x() <0) before_new_position.rx() +=8;
                if(before_new_position.x() >7) before_new_position.rx() -=8;
                if(before_new_position.y() <0) before_new_position.ry() +=8;
                if(before_new_position.y() >7) before_new_position.ry() -=8;

                if(board[before_new_position.rx()][before_new_position.ry()]->get_type() != "empty")
                {
                    Figure* figureTaken = board[before_new_position.rx()][before_new_position.ry()];
                    boardHistory.add_vanishedFig(figureTaken);
                    board[before_new_position.rx()][before_new_position.ry()] = new EmptySpace(boardPointer, before_new_position);
                    if(figureTaken->get_type() == "king")
                        return 1;

                    return 2;
                }
            }

            return 1;
        }
    }
    return 0;
}

void SGamemodBoard::after_capture(QPoint clicked_cell)
{
    selected_figure = board[clicked_cell.rx()][clicked_cell.ry()];
    selected_figure->set_move_info(1);
    selected_figure->get_moves();

    if(selected_figure->poss_moves.size())
        game_state = 22;
    else
    {
        selected_figure->set_move_info(0);
        next_turn();
    }
}

void SGamemodBoard::clicked(QPoint clicked_cell)
{
    if(game_state == 0 || game_state == -1)
    {
        if(selected_figure->get_type() == "empty" || selected_figure->get_color() != whos_turn)
        {
            selected_figure = board[clicked_cell.rx()][clicked_cell.ry()];
        }
        else
        {
            int moveReturn = move(selected_figure, clicked_cell);
            if(moveReturn == 1)
                next_turn();
            else if(moveReturn == 2)
                after_capture(clicked_cell);
            else
                selected_figure = board[clicked_cell.rx()][clicked_cell.ry()];
        }

        try_bot_move();
    }
    else if(game_state == 22)
    {
        int moveReturn = move(selected_figure, clicked_cell);
        if(moveReturn == 1)
            next_turn();
        else if(moveReturn == 2)
            after_capture(clicked_cell);

        try_bot_move();
    }
    else if(game_state > 9 && game_state < 18)
    {
        int x = game_state%10;
        if(clicked_cell.x() == x)
        {
            int y =clicked_cell.y();
            int y1 = !whos_turn * 7;
            int y2 = 4-!whos_turn;
            if((y>=y1&&y<=y2) || (y>=y2&&y<=y1))
            {
                int choise= (y1 - y);
                if(choise<0) choise*=-1;

                y = !whos_turn * 7;
                boardHistory.add_vanishedFig(board[x][y]);
                switch(choise)
                {
                case 0:
                    board[x][y] = new Queen(boardPointer, whos_turn, {x,y});
                    break;
                case 1:
                    board[x][y] = new Rook(boardPointer, whos_turn, {x,y});
                    break;
                case 2:
                    board[x][y] = new Bishop(boardPointer, whos_turn, {x,y});
                    break;
                case 3:
                    board[x][y] = new Knight(boardPointer, whos_turn, {x,y});
                    break;
                case 4:
                    board[x][y] = new Pawn(boardPointer, whos_turn, {x,y});
                    break;
                }
                boardHistory.add_setFig(board[x][y]);
                next_turn();
                try_bot_move();
            }
        }
    }
}
