#ifndef COMPUTERMEDIUM_H
#define COMPUTERMEDIUM_H
#include "player.h"

class ComputerMedium : public Player {
    public:
		ComputerMedium(Colour colour, PlayerType type);
		~ComputerMedium();
		Move computerMoveChoice(std::vector<Move> validMoves) override;
};


#endif
