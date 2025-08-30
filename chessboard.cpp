#include "chessboard.h"

ChessBoard::ChessBoard():
    BoardData(), kings{King(&board,0, {4,0}),King(&board,1,{4,7})}
{
    set_new_board();
    update_board();
}

ChessBoard::~ChessBoard()
{
    delete_board();
}

void ChessBoard::get_itsCheck_moves(int checkCount)
{
    itsCheck_moves.clear();

    QString checking_type = board[kings[whos_turn].get_check_position().x()][kings[whos_turn].get_check_position().y()]->get_type();
    if(checkCount == 1 &&  checking_type != "knight")
    {
        QPoint pos1 = kings[whos_turn].get_position();
        QPoint pos2 = kings[whos_turn].get_check_position();
        QPoint direction = {pos2.x()-pos1.x() > 0, pos2.y()-pos1.y() > 0};
        direction.rx() -= pos2.x()-pos1.x() < 0;
        direction.ry() -= pos2.y()-pos1.y() < 0;

        QPoint a(fmin(pos1.x(),pos2.x()) , fmin(pos1.y(),pos2.y())), b(fmax(pos1.x(),pos2.x()) , fmax(pos1.y(),pos2.y()));
        QRect range(a,b);
        for(QPoint current_pos = pos1 + direction; range.contains(current_pos);current_pos+=direction)
            itsCheck_moves.push_back(current_pos);
    }
    else if(checking_type == "knight")
        itsCheck_moves.push_back(kings[whos_turn].get_check_position());
}

void ChessBoard::set_new_board()
{
    kings[0].set_position({4,0});
    kings[1].set_position({4,7});
    kings[0].reset_move_info();
    kings[1].reset_move_info();

    selected_figure = &universal_empty;

    for(int x=0;x<8;x++)
        for(int y=2;y<6;y++)
            board[x][y] = new EmptySpace(boardPointer, {x, y});


    for(int i=0;i<8;i++)
    {
        board[i][1] = new Pawn(boardPointer,0, {i, 1});
        board[i][6] = new Pawn(boardPointer,1, {i, 6});
    }

    board[0][0] = new Rook(boardPointer, 0, {0,0});
    board[7][0] = new Rook(boardPointer, 0, {7,0});
    board[0][7] = new Rook(boardPointer, 1, {0,7});
    board[7][7] = new Rook(boardPointer, 1, {7,7});

    board[2][0] = new Bishop(boardPointer, 0, {2,0});
    board[5][0] = new Bishop(boardPointer, 0, {5,0});
    board[2][7] = new Bishop(boardPointer, 1, {2,7});
    board[5][7] = new Bishop(boardPointer, 1, {5,7});

    board[1][0] = new Knight(boardPointer, 0, {1,0});
    board[6][0] = new Knight(boardPointer, 0, {6,0});
    board[1][7] = new Knight(boardPointer, 1, {1,7});
    board[6][7] = new Knight(boardPointer, 1, {6,7});

    board[3][0] = new Queen(boardPointer, 0, {3,0});
    board[3][7] = new Queen(boardPointer, 1, {3,7});

    board[4][0] = &kings[0];
    board[4][7] = &kings[1];

    whos_turn = 1;
    game_state = -1;
}

void ChessBoard::update_board()
{
    for(int x=0;x<8;x++)
    {
        for(int y=0;y<8;y++)
        {
            board[x][y]->erease_variables();
            if(board[x][y]->get_type() =="pawn" && board[x][y]->get_color() != whos_turn && board[x][y]->get_move_info() != 0)
            {
                boardHistory.add_movedFig({x,y},{x,y}, board[x][y]->get_move_info(), 0);
                board[x][y]->set_move_info(0);
            }
        }
    }
    for(int x=0;x<8;x++)
    {
        for(int y=0;y<8;y++)
        {
            if(board[x][y]->get_type() != "king") board[x][y]->next_turn();
        }
    }

    kings[whos_turn].pin_and_check();

    if(kings[whos_turn].get_isAttacked(!whos_turn))
    {
        itsCheck =1;
        get_itsCheck_moves(kings[whos_turn].get_isAttacked(!whos_turn));
    }else itsCheck =0;

    int total_moves = 0;
    for(int x=0;x<8;x++)
    {
        for(int y=0;y<8;y++)
        {
            if(board[x][y]->get_type() != "king")
            {
                board[x][y]->get_moves();
                if(itsCheck) board[x][y]->filter_moves(itsCheck_moves);
                if(board[x][y]->get_color() == whos_turn)
                    total_moves+= board[x][y]->poss_moves.size();
            }
        }
    }
    kings[0].attack();
    kings[1].attack();
    kings[0].get_moves();
    kings[1].get_moves();
    total_moves+=kings[whos_turn].poss_moves.size();
    if(total_moves ==0)
    {
        if(itsCheck)
            game_state = 1;
        else
            game_state = 2;
    }
}

void ChessBoard::delete_board()
{
    for(int x=0;x<8;x++)
        for(int y=0;y<8;y++)
            board[x][y]->move({x,y});
    boardHistory.delete_history(boardPointer);
    for(int x=0;x<8;x++)
        for(int y=0;y<8;y++)
            if(board[x][y]->get_type()!="king")
                delete board[x][y];
}

int ChessBoard::move(Figure *figure, QPoint new_position)
{
    for(int i=0; i<figure->poss_moves.size();i++)
    {
        if(figure->poss_moves[i] == new_position)
        {
            QPoint old_position = figure->get_position();
            int old_move_info = figure->get_move_info();

            if(figure->get_type() == "pawn")
            {
                if(old_position.rx() != new_position.rx() && board[new_position.rx()][new_position.ry()]->get_type() == "empty")
                {
                    QPoint en_passant(new_position.rx(),old_position.ry());
                    boardHistory.add_vanishedFig(board[en_passant.rx()][en_passant.ry()]);
                    board[en_passant.rx()][en_passant.ry()] = new EmptySpace(boardPointer,en_passant);
                }
                if((new_position.y() - old_position.y() == 2) || (new_position.y() - old_position.y() == -2))
                {
                    Figure* en_passant_pawn;
                    if(new_position.x()>0)
                    {
                        Figure* en_passant_pawn = board[new_position.x() -1][new_position.y()];
                        if(en_passant_pawn->get_type() == "pawn" && en_passant_pawn->get_color() != whos_turn)
                        {
                            en_passant_pawn->set_move_info(1);
                            boardHistory.add_movedFig(en_passant_pawn->get_position(), en_passant_pawn->get_position(), 0,1);
                        }
                    }
                    if(new_position.x()<7)
                    {
                        en_passant_pawn = board[new_position.x() +1][new_position.y()];
                        if(en_passant_pawn->get_type() == "pawn" && en_passant_pawn->get_color() != whos_turn)
                        {
                            en_passant_pawn->set_move_info(-1);
                            boardHistory.add_movedFig(en_passant_pawn->get_position(), en_passant_pawn->get_position(), 0,-1);
                        }
                    }
                }
            }

            boardHistory.add_vanishedFig(board[new_position.rx()][new_position.ry()]);

            board[new_position.rx()][new_position.ry()] = figure;
            board[new_position.rx()][new_position.ry()]->move(new_position);
            int new_move_info = board[new_position.rx()][new_position.ry()]->get_move_info();
            board[old_position.rx()][old_position.ry()] = new EmptySpace(boardPointer,old_position);

            boardHistory.add_movedFig(old_position,new_position, old_move_info, new_move_info);

            if(figure->get_type() == "pawn" && (new_position.ry() == 0 || new_position.ry()== 7)) /// PAWN PROMOTION
            {
                game_state = 10 + new_position.x();
                return 2;
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
            return 1;
        }
    }
    return 0;
}

void ChessBoard::clicked(QPoint clicked_cell)
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
