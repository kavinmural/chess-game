#ifndef PLAYER_H
#define PLAYER_H
#include "colour.h"
#include "move.h"
#include <vector>

enum PlayerType{Human, CPU};

class Player{
    public:
    Colour colour;
    PlayerType type;
    Player(Colour, PlayerType);
    virtual ~Player();
    virtual Move computerMoveChoice(std::vector<Move> validMoves);
};

#endif
