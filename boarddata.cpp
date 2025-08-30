#include "boarddata.h"

bool BoardData::bot_enabled = 0;
bool BoardData::bot_color = 0;

BoardData::BoardData()
    : boardPointer(&board), universal_empty(&board, {0,0})
{
}

BoardData::~BoardData()
{
}

void BoardData::set_new_board()
{
    selected_figure = &universal_empty;

    for(int x=0;x<8;x++)
        for(int y=0;y<8;y++)
            board[x][y] = new EmptySpace(boardPointer, {x, y});

    whos_turn = 1;
    game_state = -1;
}

void BoardData::delete_board()
{
    for(int x=0;x<8;x++)
        for(int y=0;y<8;y++)
            board[x][y]->move({x,y});

    boardHistory.delete_history(boardPointer);
    for(int x=0;x<8;x++)
        for(int y=0;y<8;y++)
            delete board[x][y];
}

int BoardData::move(Figure *figure, QPoint new_position)
{
    for(int i=0; i<figure->poss_moves.size();i++)
    {
        if(figure->poss_moves[i] == new_position)
        {
            QPoint old_position = figure->get_position();
            int old_move_info = figure->get_move_info();

            boardHistory.add_vanishedFig(board[new_position.rx()][new_position.ry()]);

            board[new_position.rx()][new_position.ry()] = figure;
            board[new_position.rx()][new_position.ry()]->move(new_position);
            int new_move_info = board[new_position.rx()][new_position.ry()]->get_move_info();
            board[old_position.rx()][old_position.ry()] = new EmptySpace(boardPointer,old_position);

            boardHistory.add_movedFig(old_position,new_position, old_move_info, new_move_info);
            return 1;
        }
    }
    return 0;
}

void BoardData::next_turn()
{
    if(whos_turn)
        whos_turn = 0;
    else
        whos_turn = 1;
    game_state = 0;
    selected_figure = &universal_empty;
    boardHistory.save_move();
    update_board();
}

void BoardData::undo()
{
    if(boardHistory.undo(boardPointer))
    {
        if(whos_turn)
            whos_turn = 0;
        else
            whos_turn = 1;
    }
    game_state = 0;
    selected_figure = &universal_empty;
    update_board();
}

void BoardData::redo()
{
    if(boardHistory.redo(boardPointer))
    {
        if(whos_turn)
            whos_turn = 0;
        else
            whos_turn = 1;
    }
    game_state = 0;
    selected_figure = &universal_empty;
    update_board();
}

void BoardData::timesUp(bool color)
{
    whos_turn = color;
    game_state = 19;
}

void BoardData::reset()
{
    delete_board();
    set_new_board();
    update_board();
}

void BoardData::clicked(QPoint clicked_cell)
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
            else
                selected_figure = board[clicked_cell.rx()][clicked_cell.ry()];
        }

        try_bot_move();
    }
}

void BoardData::get_marks(bool (&marks)[8][8])
{
    if(bot_marks.size())
    {
        for(int i = 0; i<bot_marks.size();i++)
            marks[bot_marks[i].rx()][bot_marks[i].ry()] = 1;

        bot_marks.clear();
    }
    else if(selected_figure->get_type() != "empty" && selected_figure->get_color() == whos_turn)
    {
        for(int i=0;i<selected_figure->poss_moves.size();i++)
            marks[selected_figure->poss_moves[i].rx()][selected_figure->poss_moves[i].ry()] = 1;
        marks[selected_figure->get_position().rx()][selected_figure->get_position().ry()] = 1;
    }
}

void BoardData::try_bot_move()
{
    if(bot_enabled && whos_turn == bot_color)
    {
        if(game_state == -1 || game_state == 0)
        {
            QList<QPoint> bot_color_figures;

            for(int x=0;x<8;x++)
                for(int y=0;y<8;y++)
                    if(board[x][y]->get_color() == bot_color && board[x][y]->poss_moves.size()) bot_color_figures.append({x,y});

            int random_index = rand()%bot_color_figures.size();
            selected_figure = board[bot_color_figures[random_index].x()][bot_color_figures[random_index].y()];
            random_index = rand()%selected_figure->poss_moves.size();
            bot_marks.append({selected_figure->get_position(), selected_figure->poss_moves[random_index]});

            clicked(selected_figure->poss_moves[random_index]);
        }
        if(game_state > 9 && game_state < 18)
        {
            QPoint choice;
            choice.rx() = game_state -10;
            choice.ry() = rand()%5;
            if(!bot_color) choice.ry() +=3;

            clicked(choice);
        }
        if(game_state == 22)
        {
            int random_index = rand()%selected_figure->poss_moves.size();
            bot_marks.append({selected_figure->get_position(), selected_figure->poss_moves[random_index]});

            clicked(selected_figure->poss_moves[random_index]);
        }
    }
}
