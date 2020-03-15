#include <iostream>
#include <string>
#include "game.h"
//#include "player.h"
using namespace std;

int main(int argc, char* argv[]) {
	string command;
	Game* game;
	Builder* builder = nullptr;

	while (cin >> command) {

		if (command == "game") {
			string playerOne;
			string playerTwo;
			cin >> playerOne >> playerTwo;
			game = new Game{playerOne, playerTwo, builder};
		} else if (command == "move"){
			if (game->getCurrentPlayerType() == PlayerType::CPU) {
				game->move();
			} else {
				string oldCoordinate;
				string newCoordinate;
				cin >> oldCoordinate >> newCoordinate;
				game->move(oldCoordinate, newCoordinate);
			}
		} else if (command == "resign") {
			game->resign();
		} else if (command == "setup") {
			builder = Game::setup();
		}
	}
	if(game != nullptr){
		game->endGame();
		delete game;
	}
}
