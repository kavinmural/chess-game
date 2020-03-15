#ifndef COMPUTEREASY_H
#define COMPUTEREASY_H
#include "player.h"

enum Colour;
enum PlayerType;

class ComputerEasy: public Player {
    public:
		ComputerEasy(Colour colour, PlayerType type);
		~ComputerEasy()override;
		Move computerMoveChoice(std::vector<Move> validMoves) override;
};

#endif
