#include "computermedium.h"
#include "move.h"
#include <stdlib.h>
using namespace std;

ComputerMedium::ComputerMedium(Colour colour, PlayerType type) : Player{colour, type} {}

ComputerMedium::~ComputerMedium(){}

Move ComputerMedium::computerMoveChoice(vector<Move> validMoves) {
	for (Move m : validMoves) {
		if (m.moveType == MoveType::Capture || m.moveType == MoveType::EnPassant) return m;
	}

	for (Move m : validMoves) {
		if (m.moveType == MoveType::Check) return m;
	}
        int random = rand() % (validMoves.size() - 1);
        return validMoves[random];
}
