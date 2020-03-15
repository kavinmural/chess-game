#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <string>

#include "board.h"
#include "scoreboard.h"
#include "player.h"

class Builder;

class Game{
    Board* board;
    ScoreBoard scoreboard;
    Player* currentPlayer;
    Player* playerOne;
    Player* playerTwo;
    public:
    	Game(std::string playerOne, std::string playerTwo, Builder* builder);
		~Game();

    	PlayerType getCurrentPlayerType();
    	void resign();
    	void move(std::string oldCoordinate, std::string newCoordinate);
		void move();
		void endGame();
		static Builder* setup();
};
#endif
