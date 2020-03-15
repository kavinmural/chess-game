#ifndef MOVE_H
#define MOVE_H
#include <string>
#include "board.h"

enum MoveType{Default, Capture, Check, Avoid, Promotion, CastlingK, CastlingQ,  EnPassant};

struct Move{
    MoveType moveType = MoveType::Default;
    int oldCoord;
    int newCoord;
    Move(int, int);
    ~Move();
};

#endif
