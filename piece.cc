#include <vector>
#include <iostream>
#include "piece.h"
#include "builder.h"
using namespace std;


Piece::Piece(Colour colour, PieceType type, int coordinate, vector<int> moveOffsets)
	: colour{colour}, type{type}, coordinate{coordinate}, moveOffsets{moveOffsets} {}

int Piece::getCoordinate() const {
	return this->coordinate;
}

PieceType Piece::getPieceType() const {
	return this->type;
}

Colour Piece::getColour() const {
	return this->colour;
}

void Piece::setCoordinate(int coord){
	this->coordinate = coord;
}

vector<Move> Piece::getLegalMoves(Builder *builder, vector<Move> moves) {
	vector<Move> newMoves;
	builder->setIsMock(true);
	builder->setIsSetup(false);
	for (Move m : moves) {
		int oldCoordinate = m.oldCoord;
		int newCoordinate = m.newCoord;
		Piece* stationaryPiece = builder->getPiece(newCoordinate);
		builder->removePiece(newCoordinate);
		this->setCoordinate(newCoordinate);

		builder->removePiece(oldCoordinate);
		builder->setPiece(this);
		Board *tempBoard = builder->build();
		// Check MoveType
		Colour tempColour = this->getColour();
		Colour opposingColour = Colour::Black;
		if(tempColour == Colour::Black) opposingColour = Colour::White;
		if(tempBoard->isCheck(opposingColour)) m.moveType = MoveType::Check;
		// Check MoveType
		if (!(tempBoard->isCheck(this->getColour()))) newMoves.emplace_back(m);
		this->setCoordinate(oldCoordinate);
		builder->removePiece(newCoordinate);
		if(stationaryPiece != nullptr){
			stationaryPiece->setCoordinate(newCoordinate);
		}
		builder->setPiece(this);
		if(stationaryPiece != nullptr){
			builder->setPiece(stationaryPiece);
		}
		delete tempBoard;
	}
	builder->setIsMock(false);
	return newMoves;
}

