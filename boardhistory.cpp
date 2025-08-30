#include "boardhistory.h"

BoardHistory::BoardHistory()
{
    new_snapshot();
    move_num =0;
}

void BoardHistory::add_setFig(Figure *changed_figure)
{
    int id = ++action_order_in;
    if(id > 10000) id-=10000;
    if(action_order_in > 10000) action_order_in-=10000;
    while(action_order_out != id) {}

    cut_future_moves();
    move_history[move_num].orderOfActions.push_back(100 + move_history[move_num].set_figures.size());
    move_history[move_num].set_figures.push_back(changed_figure);

    action_order_out++;
}

void BoardHistory::add_vanishedFig(Figure *changed_figure)
{
    int id = ++action_order_in;
    if(id > 10000) id-=10000;
    if(action_order_in > 10000) action_order_in-=10000;
    while(action_order_out != id) {}

    cut_future_moves();
    if(changed_figure->get_type() == "empty")
        delete changed_figure;
    else
    {
        move_history[move_num].orderOfActions.push_back(200 + move_history[move_num].vanished_figures.size());
        move_history[move_num].vanished_figures.push_back(changed_figure);
    }

    action_order_out++;
}

void BoardHistory::add_movedFig(QPoint old_position, QPoint new_position, int info1, int info2)
{
    int id = ++action_order_in;
    if(id > 10000) id-=10000;
    if(action_order_in > 10000) action_order_in-=10000;
    while(action_order_out != id) {}

    if(old_position == new_position)
    {
        if(move_history[move_num].isThere_move(old_position, new_position, info1, info2))
        {
            action_order_out++;
            return;
        }
    }
    cut_future_moves();
    move_history[move_num].orderOfActions.push_back(300 + move_history[move_num].moved_figures[0].size());
    move_history[move_num].moved_figures[0].push_back(old_position);
    move_history[move_num].moved_figures[1].push_back(new_position);
    move_history[move_num].move_info[0].push_back(info1);
    move_history[move_num].move_info[1].push_back(info2);


    action_order_out++;
}

void BoardHistory::save_move()
{
    int id = ++action_order_in;
    if(id > 10000) id-=10000;
    if(action_order_in > 10000) action_order_in-=10000;
    while(action_order_out != id) {}

    move_history[move_num].stored = 1;
    move_num++;

    new_snapshot();

    action_order_out++;
}

bool BoardHistory::undo(Figure *(*board)[8][8])
{
    if(!can_undo()) return 0;

    int id = ++action_order_in;
    if(id > 10000) id-=10000;
    if(action_order_in > 10000) action_order_in-=10000;
    while(action_order_out != id) {}


    if(move_history[move_num].stored || move_history[move_num].isEmpty())
    {
        move_num--;
        reverse_move(board,move_history[move_num]);
        action_order_out++;
        return 1;
    }

    reverse_move(board,move_history[move_num]);
    move_history[move_num].clear();
    action_order_out++;
    return 0;
}

bool BoardHistory::redo(Figure *(*board)[8][8])
{
    if(!can_redo()) return 0;

    int id = ++action_order_in;
    if(id > 10000) id-=10000;
    if(action_order_in > 10000) action_order_in-=10000;
    while(action_order_out != id) {}

    repeat_move(board, move_history[move_num]);
    move_num++;
    action_order_out++;
    return 1;
}

bool BoardHistory::can_undo()
{
    if(move_num<1) return 0;
    return 1;
}
bool BoardHistory::can_redo()
{
    if(move_num >= move_history.size() - 1) return 0;
    return 1;
}

void BoardHistory::delete_history(Figure *(*board)[8][8])
{
    for(int i = 0; i<move_history.size();i++)
    {
        for(int j = 0; j<move_history[i].vanished_figures.size();j++)
        {
            int x = move_history[i].vanished_figures[j]->get_position().x();
            int y = move_history[i].vanished_figures[j]->get_position().y();
            if(move_history[i].vanished_figures[j] != (*board)[x][y])
                delete move_history[i].vanished_figures[j];
        }
        for(int j = 0; j<move_history[i].set_figures.size();j++)
        {
            int x = move_history[i].set_figures[j]->get_position().x();
            int y = move_history[i].set_figures[j]->get_position().y();
            if(move_history[i].set_figures[j] != (*board)[x][y])
                delete move_history[i].set_figures[j];
        }
    }
    move_history.clear();
    new_snapshot();
    move_num =0;

}

void BoardHistory::reverse_move(Figure *(*board)[8][8], MoveSnapshot &snapshot)
{
    for(int i=snapshot.orderOfActions.size()-1;i>=0;i--)
    {
        int idx = snapshot.orderOfActions[i] %100;
        int type = snapshot.orderOfActions[i] /100;
        if(type==1)
        {
            int x = snapshot.set_figures[idx]->get_position().x();
            int y = snapshot.set_figures[idx]->get_position().y();
            (*board)[x][y] = new EmptySpace(board, {x,y});
        }
        if(type==2)
        {
            int x = snapshot.vanished_figures[idx]->get_position().x();
            int y = snapshot.vanished_figures[idx]->get_position().y();
            if((*board)[x][y]->get_type() == "empty") delete (*board)[x][y];
            (*board)[x][y] = snapshot.vanished_figures[idx];
        }
        if(type==3)
        {

            int xo = snapshot.moved_figures[0][idx].x();
            int yo = snapshot.moved_figures[0][idx].y();
            int xn = snapshot.moved_figures[1][idx].x();
            int yn = snapshot.moved_figures[1][idx].y();

            if((*board)[xo][yo]->get_type() == "empty") delete (*board)[xo][yo];
            (*board)[xo][yo] = (*board)[xn][yn];
            (*board)[xo][yo]->move({xo,yo});
            (*board)[xo][yo]->set_move_info(snapshot.move_info[0][idx]);
            if(xo!=xn || yo!=yn) (*board)[xn][yn] = new EmptySpace(board, {xn,yn});
        }
    }
}
void BoardHistory::repeat_move(Figure *(*board)[8][8], MoveSnapshot &snapshot)
{
    for(int i=0;i<snapshot.orderOfActions.size();i++)
    {
        int idx = snapshot.orderOfActions[i] %100;
        int type = snapshot.orderOfActions[i] /100;
        if(type==1)
        {
            int x = snapshot.set_figures[idx]->get_position().x();
            int y = snapshot.set_figures[idx]->get_position().y();
            if((*board)[x][y]->get_type() == "empty") delete (*board)[x][y];
            (*board)[x][y] = snapshot.set_figures[idx];
        }
        if(type==2)
        {
            int x = snapshot.vanished_figures[idx]->get_position().x();
            int y = snapshot.vanished_figures[idx]->get_position().y();
            (*board)[x][y] = new EmptySpace(board, {x,y});
        }
        if(type==3)
        {
            int xo = snapshot.moved_figures[0][idx].x();
            int yo = snapshot.moved_figures[0][idx].y();
            int xn = snapshot.moved_figures[1][idx].x();
            int yn = snapshot.moved_figures[1][idx].y();

            if((*board)[xn][yn]->get_type() == "empty")delete (*board)[xn][yn];
            (*board)[xn][yn] = (*board)[xo][yo];
            (*board)[xn][yn]->move({xn,yn});
            (*board)[xn][yn]->set_move_info(snapshot.move_info[1][idx]);
            if(xo!=xn || yo!=yn) (*board)[xo][yo] = new EmptySpace(board, {xo,yo});
        }
    }
}

void BoardHistory::cut_future_moves()
{
    if(move_history[move_num].stored)
    {
        for(int i = move_num; i<move_history.size();i++)
            for(int j = 0; j<move_history[i].set_figures.size(); j++)
                delete move_history[i].set_figures[j];
        move_history[move_num].clear();
        while(move_num < move_history.size()-1)
            move_history.pop_back();
    }
}

void BoardHistory::new_snapshot()
{
    move_history.push_back({});
    move_history[move_history.size() -1].clear();
}
