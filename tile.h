#ifndef TILE_H
#define TILE_H
#include "subject.h"
//#include "colour.h"

class Piece;

class Tile : public Subject {
	const int coordinate;
        const Colour colour;
	Piece* piece;

	public:
		Tile(int coordinate, Colour colour, Piece* piece);

		int getCoordinate();
		bool isOccupied();
		Piece* getPiece();
		void setPiece(Piece *p);
                Colour getColour();
		TileInfo getInfo() const override;
};
#endif
