#include "movesnapshot.h"

MoveSnapshot::MoveSnapshot()
{
    clear();
}

void MoveSnapshot::clear()
{
    set_figures.clear();
    vanished_figures.clear();
    for(int i=0;i<moved_figures[0].size();i++)
    {
        if(moved_figures[0] != moved_figures[1])
        {
            moved_figures[0].removeAt(i);
            moved_figures[1].removeAt(i);
            move_info[0].removeAt(i);
            move_info[1].removeAt(i);
            i--;
        }
    }
    orderOfActions.clear();
    stored = 0;
}

bool MoveSnapshot::isEmpty()
{
    if(!set_figures.isEmpty() || !vanished_figures.isEmpty())
        return 0;

    for(int i=0;i<moved_figures[0].size();i++)
    {
        if(moved_figures[0] != moved_figures[1])
            return 0;
    }
    return 1;
}

bool MoveSnapshot::isThere_move(QPoint old_position, QPoint new_position, int info1, int info2)
{
    for(int i=0; i<moved_figures[0].size();i++)
    {
        if(old_position == moved_figures[0][i] && new_position == moved_figures[1][i]
                && info1 == move_info[0][i] && info2 == move_info[1][i])
            return 1;
    }
    return 0;
}
