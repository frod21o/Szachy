#include "boarddisplay.h"
#include <QPaintEvent>
#include <QPainter>
#include <QRect>

#include <iostream>

BoardDisplay::BoardDisplay(QWidget *parent)
    : QWidget{parent}, boardData(new ChessBoard)
{
    clear_marks();
}

BoardDisplay::~BoardDisplay()
{
    delete boardData;
}

void BoardDisplay::clear_marks()
{
    for(int x=0;x<8;x++)
        for(int y=0;y<8;y++)
            marks[x][y] = 0;
}

void BoardDisplay::reset()
{
    boardData->reset();
    clear_marks();
    repaint();
}

void BoardDisplay::new_board_set()
{
    clear_marks();
    repaint();
}

void BoardDisplay::undo()
{
    boardData->undo();
    update_marks();
    repaint();
}

void BoardDisplay::redo()
{
    boardData->redo();
    update_marks();
    repaint();
}

void BoardDisplay::update_marks()
{
    clear_marks();
    boardData->get_marks(marks);
}

void BoardDisplay::paintEvent(QPaintEvent *e)
{
    QSize f(5,5);
    frameS = this->frameSize() - f;
    beginPoint = {0,0};

    if(frameS.rheight()>frameS.rwidth())
    {
        frameS.rwidth() -= frameS.rwidth()%8;
        frameS.rheight() = frameS.rwidth();
    }
    else
    {
        frameS.rheight() -= frameS.rheight()%8;
        frameS.rwidth() = frameS.rheight();
    }

    beginPoint.rx() = (this->frameSize().rwidth() - frameS.rwidth()) /2;
    beginPoint.ry() = (this->frameSize().rheight() - frameS.rheight()) /2;

    e->accept();
    QPainter p(this);

    // #eeeed2,#baca44
    QColor white(238,238,210);
    QColor black(186,202,68);
    QColor mark_color(120,120,250);
    QColor checkMark_color(200,40,40, 150);

    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            QPoint currentPoint = beginPoint;
            currentPoint.rx() += i *frameS.rwidth()/8;
            currentPoint.ry() += j *frameS.rheight()/8;
            QRect cell(currentPoint, frameS /8);

            int x,y;
            if((invert_board == 2 && !boardData->get_turn()) || invert_board == 0)
                x=7-i, y=7-j;
            else
                x=i, y=j;

            if((x+y)%2 == 0)
                p.fillRect(cell, white);
            else
                p.fillRect(cell,black);

            if(boardData->get_itsCheck() && boardData->board[x][y]->get_type() == "king" && boardData->board[x][y]->get_color() == boardData->get_turn())
                p.fillRect(cell, {200,100,100});

            int margins=-1;
            if(marks[x][y] && (boardData->get_game_state() == 0 || boardData->get_game_state() == -1 || boardData->get_game_state() == 22))
            {
                p.fillRect(cell, {200,200,200}),
                p.fillRect(cell.marginsAdded(QMargins(margins,margins,margins,margins)), mark_color);
            }

            if(boardData->get_itsCheck() && boardData->board[x][y]->get_type() == "king" && boardData->board[x][y]->get_color() == boardData->get_turn())
                p.fillRect(cell, checkMark_color);

            if(boardData->board[x][y]->get_type() != "empty" )
                p.drawImage(cell, boardData->board[x][y]->get_image());
        }
    }

    QRect frame (beginPoint, frameS);
    QColor grey(100,100,100,200);
    QString message;
    QFont font;
    font.setPixelSize(frameS.height()/16);
    p.setFont(font);
    switch(boardData->get_game_state())
    {
    case 1:
        p.fillRect(frame, grey);
        if(boardData->get_turn())
            message = "Szach mat\nWygrywają czarne";
        else
            message = "Szach mat\nWygrywają białe";
        p.drawText(frame,132,message);
        break;
    case 2:
        p.fillRect(frame, grey);
        font.setPixelSize(frameS.height()/20);
        p.setFont(font);
        if(boardData->get_turn())
            message = "Pat\nCBiałe nie mają dostępnych ruchów,\nwięc jest remis";
        else
            message = "Pat\nCzarne nie mają dostępnych ruchów,\nwięc jest remis";
        p.drawText(frame,132,message);
        break;
    case 19:
        p.fillRect(frame, grey);
        if(boardData->get_turn())
            message = "Koniec czasu\nWygrywają czarne";
        else
            message = "Koniec czasu\nWygrywają białe";
        p.drawText(frame,132,message);
        break;
    case 21:
        p.fillRect(frame, grey);
        if(boardData->get_turn())
            message = "Koniec gry\nWygrywają czarne";
        else
            message = "Koniec gry\nWygrywają białe";
        p.drawText(frame,132,message);

        break;
    default:
        if(boardData->get_game_state() >=10 && boardData->get_game_state()<=17)
        {
            p.fillRect(frame, grey);
            bool isTwisted = ((invert_board == 2 && !boardData->get_turn()) || invert_board == 0);
            bool upOrDown = (boardData->get_turn() && !isTwisted) || (!boardData->get_turn() && isTwisted);
            int x = boardData->get_game_state()%10;
            if(isTwisted)
                x=7-x;
            QPoint selectionFramePoint(x, !upOrDown * 3);
            selectionFramePoint.rx() *= frameS.width() / 8;
            selectionFramePoint.ry() *= frameS.height() / 8;
            selectionFramePoint += beginPoint;
            QImage options[5];
            QString colorString;
            if(boardData->get_turn())
                colorString="white";
            else
                colorString="black";
            options[0].load(":/Figures/"+colorString+"_queen.png");
            options[1].load(":/Figures/"+colorString+"_rook.png");
            options[2].load(":/Figures/"+colorString+"_bishop.png");
            options[3].load(":/Figures/"+colorString+"_knight.png");
            options[4].load(":/Figures/"+colorString+"_pawn.png");

            for(int i=0;i<5;i++)
            {
                QPoint currentPoint = selectionFramePoint;
                currentPoint.ry() += i *frameS.rwidth()/8;
                QRect cell(currentPoint, frameS /8);
                p.fillRect(cell,black);
                p.drawRect(cell);
                int y = i;
                if(upOrDown == 0)
                    y = 4-i;
                p.drawImage(cell,options[y]);
            }
        }
        break;
    }
    p.drawRect(frame);
}

void BoardDisplay::mousePressEvent(QMouseEvent *e)
{
    e->accept();
    QPoint clickPoint = e->pos();
    QRect frame (beginPoint, frameS);
    if(frame.contains(clickPoint, true))
    {
        clickPoint = clickPoint - beginPoint;
        clickPoint.rx() = clickPoint.rx() / (frameS.rwidth() /8);
        clickPoint.ry() = clickPoint.ry() / (frameS.rheight() /8);
        if(((invert_board == 2 && !boardData->get_turn()) || invert_board == 0))
        {
            clickPoint.rx() = 7 - clickPoint.rx();
            clickPoint.ry() = 7 - clickPoint.ry();
        }

        boardData->clicked(clickPoint);
        update_marks();
    }
    repaint();
}
