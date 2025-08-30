#ifndef BOARDDISPLAY_H
#define BOARDDISPLAY_H

#include "chessboard.h"
#include "checkersboard.h"
#include "sgamemodboard.h"

#include "QWidget"

class BoardDisplay: public QWidget
{
    Q_OBJECT
public:
    explicit BoardDisplay(QWidget *parent = nullptr);
    ~BoardDisplay();

private:
    QSize frameS;
    QPoint beginPoint;

    int invert_board = 1; // 0,1 black or white on the bottom, 2 moving player on the bottom
    bool marks[8][8];
    void clear_marks();
    void update_marks();
public:
    BoardData* boardData;

    void reset();
    void new_board_set();
    void undo();
    void redo();

    inline void invert(int mode){invert_board = mode;};
    inline int is_inverting(){return invert_board;};
private slots:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);

};

#endif // BOARDDISPLAY_H
