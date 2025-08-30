#ifndef KING_H
#define KING_H

#include "figure.h"

class King : public Figure
{
public:
    King(Figure *(*board)[8][8], int color, QPoint position);
    ~King();

    void get_moves();
    void attack();
    void move(QPoint target);

    void pin_and_check();
    inline QPoint get_check_position(){return check_position;};

    inline void add_check(QPoint position) {check_position = position;};

    inline void reset_move_info() {move_info = 1;};
private:
    QPoint check_position={-1,-1};

    int convert_direction_PtoV(QPoint direction_point);
};

#endif // KING_H
