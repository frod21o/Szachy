#include "emptyspace.h"

EmptySpace::EmptySpace(Figure *(*board)[8][8], QPoint position):
    Figure(board, -1, position)
{
    type = "empty";
}

EmptySpace::~EmptySpace()
{

}

