#ifndef KNIGHT_H
#define KNIGHT_H
#include <vector>
#include "piece.h"

class Knight : public Piece {
        public:
        Knight(Colour colour, int coordinate)
                        : Piece{colour, PieceType::N, coordinate,{-17, -15, -10, -6, 6, 10, 15, 17}} {}
                std::vector<Move> getValidMoves(Board& b) override;
	~Knight()override;
};

std::vector<Move> Knight::getValidMoves(Board& b) {
	std::vector<Move> validMoves;
        int destCoordinate = 0;
        int coord = this->getCoordinate();
        for (int i : this->moveOffsets) {
                int col = coord % 8; 
                // calculate the dest coordinate
                destCoordinate = coord + i;
                // if not a valid coordinate
                if (destCoordinate < 0 || destCoordinate > 63) {
                        continue;
                }
                if (col == 0 && (i == -17 || i == -10|| i == 6 || i == 15)) {
                        continue;
                }
                if (col == 1 && (i == -10 || i == -6)) {
                        continue;
                } 
                if (col == 6 && (i == -6 || i == 10)) {
                        continue;
                }
                if (col == 7 && (i == 17 || i == 10|| i == -6 || i == -15)) {
                        continue;
                }
                // get dest tile from board
                Tile &destTile = b.getTile(destCoordinate);
                // move case where tile is not occupied
		if (!destTile.isOccupied()) {
                        Move valid = Move(coord,destCoordinate);
                        validMoves.push_back(valid);
                }
		else {
                        Piece* destPiece = destTile.getPiece();
                        if(destPiece->getColour() != this->getColour()){
                                Move valid = Move(coord,destCoordinate);
				valid.moveType = MoveType::Capture;
                                validMoves.push_back(valid);
			}
                }
        }
        if(validMoves.size() > 0 && !(b.getBuilder()->getIsSetup()) && !(b.getBuilder()->getIsMock())){
                std::vector<Move> legalMoves = getLegalMoves(b.getBuilder(), validMoves);
                return legalMoves;
        }
        return validMoves;
}

Knight::~Knight(){}
#endif

