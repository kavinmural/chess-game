#include "computereasy.h"
#include "move.h"
#include "colour.h"
#include <stdlib.h>
using namespace std;

ComputerEasy::ComputerEasy(Colour colour, PlayerType type) : Player{colour, type} {}

ComputerEasy::~ComputerEasy(){}

Move ComputerEasy::computerMoveChoice(vector<Move> validMoves) {
	int random = rand() % (validMoves.size() - 1);
	return validMoves[random];
}
