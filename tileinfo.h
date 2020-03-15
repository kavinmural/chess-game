#ifndef TILEINFO_H
#define TILEINFO_H
#include "colour.h"

class Piece;

struct TileInfo{
    Colour colour;
    int coordinate;
    Piece *piece;    
};

#endif
