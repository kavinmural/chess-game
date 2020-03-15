#include "player.h"

using namespace std;

Player::Player(Colour c, PlayerType type):colour{c}, type{type} {}

Player::~Player(){

}

Move Player::computerMoveChoice(vector<Move> validMoves){
	Move m = Move(0,0);
	return m;
}
