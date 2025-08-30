#include "checkersboard.h"

CheckersBoard::CheckersBoard():
    BoardData()
{
    set_new_board();
    update_board();
}

CheckersBoard::~CheckersBoard()
{
    delete_board();
}

void CheckersBoard::set_new_board()
{
    selected_figure = &universal_empty;

    for(int x=0;x<8;x++)
    {
        for(int y=0;y<3;y++)
        {
            if((x+y)%2)
                board[x][y] = new CheckersPiece(boardPointer,0, {x, y});
            else
                board[x][y] = new EmptySpace(boardPointer, {x, y});

        }

        for(int y=3;y<5;y++)
            board[x][y] = new EmptySpace(boardPointer, {x, y});


        for(int y=5;y<8;y++)
        {
            if((x+y)%2)
                board[x][y] = new CheckersPiece(boardPointer,1, {x, y});
            else
                board[x][y] = new EmptySpace(boardPointer, {x, y});
        }
    }

    whos_turn = 1;
    game_state = -1;
}

void CheckersBoard::update_board()
{
    for(int x=0;x<8;x++)
    {
        for(int y=0;y<8;y++)
        {
            board[x][y]->erease_variables();
        }
    }
    CheckersPiece::we_take[0] = 0;
    CheckersPiece::we_take[1] = 0;
    for(int x=0;x<8;x++)
    {
        for(int y=0;y<8;y++)
        {
            board[x][y]->next_turn();
        }
    }
    for(int x=0;x<8;x++)
    {
        for(int y=0;y<8;y++)
        {
            board[x][y]->get_moves();
        }
    }

    int total_figures = 0;
    for(int x=0;x<8;x++)
    {
        for(int y=0;y<8;y++)
        {
            if(board[x][y]->get_color() == whos_turn)
            {
                total_figures++;
            }
        }
    }
    if(total_figures ==0)
        game_state = 21;
}

int CheckersBoard::move(Figure *figure, QPoint new_position)
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

            QPoint before_new_position = new_position - old_position;
            before_new_position.rx() /= abs(before_new_position.rx());
            before_new_position.ry() /= abs(before_new_position.ry());
            before_new_position = new_position - before_new_position;


            if(board[before_new_position.rx()][before_new_position.ry()]->get_type() != "empty")
            {
                boardHistory.add_vanishedFig(board[before_new_position.rx()][before_new_position.ry()]);
                board[before_new_position.rx()][before_new_position.ry()] = new EmptySpace(boardPointer, before_new_position);
                return 2;
            }

            return 1;
        }
    }
    return 0;
}

void CheckersBoard::clicked(QPoint clicked_cell)
{
    if(game_state == 22)
    {
        int moveReturn = move(selected_figure, clicked_cell);
        if(moveReturn == 1)
            next_turn();
        else if(moveReturn == 2)
            after_capture(clicked_cell);

        try_bot_move();
    }
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
}

void CheckersBoard::after_capture(QPoint clicked_cell)
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

void CheckersBoard::next_turn()
{
    if(whos_turn)
        whos_turn = 0;
    else
        whos_turn = 1;
    game_state = 0;

    if(selected_figure->get_color() && selected_figure->get_position().y() == 0)
    {
        boardHistory.add_vanishedFig(selected_figure);
        board[selected_figure->get_position().rx()][selected_figure->get_position().ry()] = new CheckersQueen(boardPointer, 1, selected_figure->get_position());
        boardHistory.add_setFig(board[selected_figure->get_position().rx()][selected_figure->get_position().ry()]);
    }
    else if(!selected_figure->get_color() && selected_figure->get_position().y() == 7)
    {
        boardHistory.add_vanishedFig(selected_figure);
        board[selected_figure->get_position().rx()][selected_figure->get_position().ry()] = new CheckersQueen(boardPointer, 0, selected_figure->get_position());
        boardHistory.add_setFig(board[selected_figure->get_position().rx()][selected_figure->get_position().ry()]);
    }
    selected_figure = &universal_empty;
    boardHistory.save_move();
    update_board();
}
