#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>
#include "colour.h"

class Builder;
class Move;
class Tile;
class Piece;
class TextDisplay;
class Observer;

class Board {
	const int GRID_SIZE = 63;
	Colour currentColour;

	Builder *builder;
	std::vector<Tile> board;
	std::vector<Piece*> whitePieces;
	std::vector<Piece*> blackPieces;
	std::vector<Move> whiteValidMoves;
	std::vector<Move> blackValidMoves;

	std::vector<Piece*> getActivePieces(Colour colour);
	std::vector<Move> getValidMoves(Colour colour);
	TextDisplay* td;
	Observer *obGraphics = nullptr;

	int findKing(Colour colour);
	bool canMove(std::vector<Move> moves, Move &userMove);
	std::vector<Tile> createBoard(Builder* builder);

	public:
		Board(Builder* builder);
		~Board();
				
		void makeMove(Move m);
		static Board* createStandardBoard();
		Tile& getTile(int coordinate);
		friend std::ostream& operator<<(std::ostream& out, const Board& board);
		static Builder* setup();
		Colour getCurrentColour();
		Builder* getBuilder();
		bool isCheck(Colour colour);
		std::vector<Move> getMoves(Colour);
};

#endif
