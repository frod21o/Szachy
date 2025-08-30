#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "boarddata.h"

#include "Figures/pawn.h"
#include "Figures/rook.h"
#include "Figures/bishop.h"
#include "Figures/queen.h"
#include "Figures/knight.h"
#include "Figures/king.h"

class ChessBoard : public BoardData
{
public:
    ChessBoard();
    ~ChessBoard();

private:
    King kings[2];

    QList<QPoint> itsCheck_moves;
    void get_itsCheck_moves(int checkCount);

    void set_new_board();
    void update_board();
    void delete_board();
    int move(Figure* figure, QPoint new_position); // 0 not possible move, 1 moved, 2 pawn is promoting

public:

    void clicked(QPoint clicked_cell);
};

#endif // CHESSBOARD_H
