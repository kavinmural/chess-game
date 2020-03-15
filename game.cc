#include <string>
#include "game.h"
#include "move.h"
#include "builder.h"
#include "computereasy.h"
#include "computermedium.h"
#include "computerhard.h"

using namespace std;

Game::Game(string playerOneType, string playerTwoType, Builder* builder){
	if (playerOneType == "human") {
		playerOne = new Player(Colour::White, PlayerType::Human);
	} else {
		char c = playerTwoType[8];
		int level = c - '0';
		
		switch (level) {
			case 1: playerOne = new ComputerEasy{Colour::White, PlayerType::CPU};
					break;
			case 2: playerOne = new ComputerMedium{Colour::White, PlayerType::CPU};
					break;
			case 3: playerOne = new ComputerHard{Colour::White, PlayerType::CPU};
					break;
			case 4: // playerOne = ComputerFour{Colour::White, PlayerType::CPU, 4};
					break;
		}
	}

	if (playerTwoType == "human") {
		playerTwo = new Player(Colour::White, PlayerType::Human);
	} else {
		char c = playerTwoType[8];
		int level = c - '0';
		
		switch (level) {
			case 1: playerTwo = new ComputerEasy{Colour::Black, PlayerType::CPU};
					break;
			case 2: playerTwo = new ComputerMedium{Colour::Black, PlayerType::CPU};
					break;
			case 3: playerTwo = new ComputerHard{Colour::Black, PlayerType::CPU};
					break;
			case 4: // playerTwo = ComputerFour{Colour::White, PlayerType::CPU, 4};
					break;
		}
	}
	currentPlayer = playerOne;
	if (builder != nullptr){
		board = builder->build();
	} else {
		board = Board::createStandardBoard();
	}
	cout << *board << endl;
}

Game::~Game() {
	currentPlayer = nullptr;
	board->getBuilder()->setIsMock(false);
	board->getBuilder()->setIsSetup(false);
	delete playerOne;
	delete playerTwo;
	delete board;
}

void Game::resign() {
	if (currentPlayer->colour == Colour::White) {
		cout << "Black wins!" << endl;
		scoreboard.incrementBlackScore(1);
	} else {
		cout << "White wins!" << endl;
		scoreboard.incrementWhiteScore(1);
	}

	delete board;
	board = Board::createStandardBoard();
}

void Game::move(string oldCoordinate, string newCoordinate) {
	int old = ((8 - (oldCoordinate[1] - '0')) * 8) + (oldCoordinate[0] - 'a');
	int newC = ((8 - (newCoordinate[1] - '0')) * 8) + (newCoordinate[0] - 'a');
	Move m = Move(old, newC);

	try {
		board->makeMove(m);
		if (currentPlayer == playerOne) currentPlayer = playerTwo;
		else currentPlayer = playerOne;
		cout << *board;
	} catch (string& error) {
		if (error == "checkmate") {
			cout << *board;
			if (board->getCurrentColour() == Colour::White) {
				cout << "Checkmate! Black wins!" << endl;
				scoreboard.incrementBlackScore(1);
			} else {
				cout << "Checkmate! White wins!" << endl;
				scoreboard.incrementWhiteScore(1);
			}

			// reset game

			char c;
			cout << "Do you want to play again? (y/n)" << endl;
			cin >> c;
			
			if (c == 'y') {
				delete board;
				board = Board::createStandardBoard();
			}
		} else if (error == "stalemate") {
			cout << *board;
			cout << "Stalemate!" << endl;	
			scoreboard.incrementWhiteScore(0.5);
			scoreboard.incrementBlackScore(0.5);

			// reset game

			char c;
			cout << "Do you want to play again? (y/n)" << endl;
			cin >> c;
			
			if (c == 'y') {
				delete board;
				board = Board::createStandardBoard();
			}
		} else if (error == "illegal") {
			cout << "Illegal move! Please enter a valid move." << endl;
		}
		else if(error == "check"){
			cout << *board;
			if(board->getCurrentColour() == Colour::White){
				cout << "White is in Check!" << endl;
			}
			else{
				cout << "Black is in Check!" << endl;
			}
		}
	}
}

void Game::move(){
	try {
		Colour cpuColour = currentPlayer->colour;
		vector<Move> potentialMoves = board->getMoves(cpuColour);
		Move m = currentPlayer->computerMoveChoice(potentialMoves);
		board->makeMove(m);
		if (currentPlayer == playerOne) currentPlayer = playerTwo;
                else currentPlayer = playerOne;
	} catch (string& error) {
		if (error == "checkmate") {
			cout << "Checkmate!";
			if (board->getCurrentColour() == Colour::White) cout << "Black wins!" << endl;
			else cout << "White wins!" << endl;
		} else if (error == "stalemate") {
			cout << "Stalemate!" << endl;
		} else if (error == "invalid") {
			cout << "Illegal move! Please enter a valid move." << endl;
		}
                else if(error == "check"){
                        if(board->getCurrentColour() == Colour::White){
                                cout << "White is in Check!" << endl;
                        }
                        else{
                                cout << "Black is in Check!" << endl;
                        }
                }
	}
	cout << *board;
}

void Game::endGame() {
	cout << "Final Score:" << endl;
	cout << scoreboard << endl;
}

Builder* Game::setup() {
	Builder* builder = Board::setup();
	try {
		Board* tempBoard = builder->build();
		delete tempBoard;
		builder->setIsSetup(false);
	} catch (string& error) {
		if (error == "invalid pawn") {
			cout << "Pawns cannot be in the first or last row." << endl;
			builder = nullptr;
		}

		if (error == "white king check") {
			cout << "The white king must not be in check." << endl;
			builder = nullptr;
		}

		if (error == "black king check") {
			cout << "The black king must not be in check." << endl;
			builder = nullptr;
		}

		if (error == "more than one white king") {
			cout << "There cannot be more than one white king." << endl;
			builder = nullptr;
		}

		if (error == "more than one black king") {
			cout << "There cannot be more than one black king." << endl;
			builder = nullptr;
		}

		if (error == "white king dne") {
			cout << "White king must exist." << endl;
			builder = nullptr;
		}

		if (error == "black king dne") {
			cout << "Black king must exist." << endl;
			builder = nullptr;
		}
	}

	return builder;
}

PlayerType Game::getCurrentPlayerType() {
	return currentPlayer->type;
}
