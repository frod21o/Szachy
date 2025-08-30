#include "specialqueen.h"

SpecialQueen::SpecialQueen(Figure *(*board)[8][8], int color, QPoint position)
:SpecialChecker(board, color, position)
{
    type = "specialqueen";
    if(color)
        image.load(":/Figures/white_checkersqueen.png");
    else
        image.load(":/Figures/black_checkersqueen.png");

    int ydir = 2*!color -1;
    directions.append(
                {
                    {0, -ydir}, {-1,-ydir}, {1,-ydir},
                }
                );
}

SpecialQueen::~SpecialQueen()
{

}
