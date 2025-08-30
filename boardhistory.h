#ifndef BOARDHISTORY_H
#define BOARDHISTORY_H

#include "Figures/emptyspace.h"
#include "movesnapshot.h"

class BoardHistory
{
public:
    BoardHistory();

    void add_setFig(Figure* changed_figure);
    void add_vanishedFig(Figure* changed_figure);
    void add_movedFig(QPoint old_position, QPoint new_position, int info1, int info2);

    void save_move();

    bool undo(Figure *(*board)[8][8]);
    bool redo(Figure *(*board)[8][8]);
    bool jump_to(Figure *(*board)[8][8], int move_num);

    bool can_undo();
    bool can_redo();
    inline int get_move_num() {return move_num;}

    void delete_history(Figure *(*board)[8][8]);
private:
    int move_num=-1;

    QList<MoveSnapshot> move_history;

    void reverse_move(Figure *(*board)[8][8], MoveSnapshot &snapshot);
    void repeat_move(Figure *(*board)[8][8], MoveSnapshot &snapshot);

    void cut_future_moves();
    void new_snapshot();

    int action_order_in =0;
    int action_order_out = 1;
};

#endif // BOARDHISTORY_H
