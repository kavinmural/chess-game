#include "tile.h"

Tile::Tile(const int coordinate, Colour colour, Piece* piece)
	: coordinate{coordinate}, colour{colour}, piece{piece} {}

int Tile::getCoordinate() {
	return coordinate;
}

Piece* Tile::getPiece() {
	if(this->piece != nullptr){
	    return this->piece;
    }

	return nullptr;
}

bool Tile::isOccupied(){
	return this->piece != nullptr;
}

Colour Tile::getColour(){
	return this->colour;
}

void Tile::setPiece(Piece *p){
	this->piece = p;
}

TileInfo Tile::getInfo()const{
	return TileInfo{colour, coordinate, piece};
}
