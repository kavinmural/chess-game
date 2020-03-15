#ifndef COMPUTER_H
#define COMPUTER_H
#include <vector>
#include "player.h"

class Move;
enum Colour;

class Computer : public Player {
    public:
		Computer(Colour colour, PlayerType type);
		virtual Move computerMoveChoice(std::vector<Move> validMoves) const = 0;
};

#endif
