#include "computerhard.h"
#include "move.h"
#include <stdlib.h>
using namespace std;

ComputerHard::ComputerHard(Colour colour, PlayerType type) : Player{colour, type} {}

ComputerHard::~ComputerHard(){}

Move ComputerHard::computerMoveChoice(vector<Move> validMoves) {
	for (Move m : validMoves) {
		if (m.moveType == MoveType::Capture || m.moveType == MoveType::EnPassant) return m;
	}
	for (Move m : validMoves) {
		if (m.moveType == MoveType::Check) return m;
	}
        for (Move m : validMoves) {
                if (m.moveType == MoveType::Avoid) return m;
        }
        int random = rand() % (validMoves.size() - 1);
        return validMoves[random];
}
