#ifndef BOARDDATA_H
#define BOARDDATA_H

#include "Figures/emptyspace.h"
#include "boardhistory.h"

class BoardData
{
public:
    BoardData();
    virtual ~BoardData();
protected:
    Figure *(*boardPointer)[8][8];

    bool whos_turn = 1;
    int game_state = 0; // -1 game didnt start yet, 0 normal game, 19 time run out
                        // for chess (1-18): 1 mate, 2 stalemate, , 10 - 17 pawn promotion:  0-7 x position of promoting pawn;
                        // for checkers (21-25): 21 end of the game, 22 while multiple capturing;
    Figure *selected_figure;
    EmptySpace universal_empty;

    bool itsCheck = 0;

    virtual void set_new_board();
    virtual void update_board(){};
    virtual void delete_board();
    virtual int move(Figure* figure, QPoint new_position); // 0 not possible move, 1 moved
                                                           // 2 in chess: pawn is promoting, in checkers:
    virtual void next_turn();

    BoardHistory boardHistory;
public:
    Figure *board[8][8];
    void undo();
    void redo();
    inline bool can_undo() {return boardHistory.can_undo();}
    inline bool can_redo() {return boardHistory.can_redo();}
    inline int get_move_num(){return boardHistory.get_move_num();};

    inline bool get_turn(){return whos_turn;};
    inline bool get_itsCheck(){return itsCheck;};
    inline int get_game_state(){return game_state;};

    void reset();
    void timesUp(bool color);
    virtual void clicked(QPoint clicked_cell);
    void get_marks(bool (&marks)[8][8]);

    static bool bot_enabled;
    static bool bot_color;
    QList<QPoint> bot_marks;
    void try_bot_move();
};

#endif // BOARDDATA_H
