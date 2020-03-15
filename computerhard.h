#ifndef COMPUTERHARD_H
#define COMPUTERHARD_H
#include "player.h"

class ComputerHard : public Player {
    public:
		ComputerHard(Colour colour, PlayerType type);
		~ComputerHard();
		Move computerMoveChoice(std::vector<Move> validMoves)  override;
};

#endif
