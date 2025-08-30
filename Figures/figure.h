#ifndef FIGURE_H
#define FIGURE_H

#include "vector"
#include "string"

#include <QString>
#include <QPoint>
#include <QList>
#include <QImage>

class Figure
{
public:
    Figure(Figure *(*board)[8][8], int color,QPoint position);
    virtual ~Figure();
protected:

    QString type="";
    int color;    // 0 -> black piece, 1 -> white piece, -1 -> empty space
    QPoint position;
    QImage image;

    int move_info = 0; //true for king and rook until they move, true for pawn, who can be taken en passant, true for checkers piece who just took another piece
    int isAttacked[2]={0,0};
    bool pinningDirections[2] = {0,0};  // [0] can/cant pin vertically or horizontally. [1] can/cant pin diagonally
    int isPinned=0; // 0 figure is free, 1 pinned vertical, 2 pinned horizontal, 3 pinned along positive diagonal, 4 pinned along negative diagonal
    bool i_see_king=0;

    void diagonal_move();
    void hv_move();
    void diagonal_attack();
    void hv_attack();
public:
    Figure *(*board)[8][8];
    QList<QPoint> poss_moves;

    inline QString get_type() {return type;};
    inline int get_color() {return color;};
    inline QPoint get_position() {return position;};
    inline QImage get_image() {return image;};

    inline int get_move_info() {return move_info;};
    inline void set_move_info(int inf) {move_info = inf;};
    inline int get_isAttacked(bool color) {return isAttacked[color];};
    inline bool get_i_see_king() {return i_see_king;};
    inline void under_attack(bool color) {isAttacked[color]++;};
    inline void pin(int direction) {isPinned = direction;};
    inline bool get_pinningDirections(int id) {return pinningDirections[id];};
    inline void set_position(QPoint position){this->position = position;};
    void erease_variables();

    virtual void get_moves() {};
    virtual void attack(); // 0 error, 1 sucess, 2 check
    virtual void next_turn();
    virtual void move(QPoint target);
    void filter_moves(QList<QPoint> &filter_list);

    virtual void add_check(QPoint position) {position ={0,0};};
};

#endif // FIGURE_H
