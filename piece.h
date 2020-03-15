#ifndef PIECE_H
#define PIECE_H
#include <iostream>
#include <string>
#include <vector>
#include "tile.h"
#include "move.h"

enum PieceType{K,Q,B,N,R,P};
class Board;
class Builder;

class Piece {
    const Colour colour;
    PieceType type;
    int coordinate;
    protected:
    	std::vector<int> moveOffsets;
	std::vector<Move> getLegalMoves(Builder *builder, std::vector<Move> m);
    public:
    	bool isFirstMove = true;
	bool isSecondMove = false;
    public:
	Piece(Colour colour, PieceType type, int coordinate, std::vector<int> moveOffsets);
        virtual std::vector<Move> getValidMoves(Board& b) = 0;
        int getCoordinate() const;
	void setCoordinate(int c);
        PieceType getPieceType() const;
        Colour getColour() const;
		virtual ~Piece() = default;
};
#endif
