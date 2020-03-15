#ifndef QUEEN_H
#define QUEEN_H
#include <vector>
#include "piece.h"


class Queen : public Piece{
	public:
        Queen(Colour colour, int coordinate)
			: Piece{colour, PieceType::Q, coordinate, {-9, -8, -7, -1, 1, 7, 8, 9}} {}
		std::vector<Move> getValidMoves(Board& b);
	~Queen()override;
};

std::vector<Move> Queen::getValidMoves(Board& b) {
    	std::vector<Move> validMoves;
        int destCoordinate = 0;
        int coord = this->getCoordinate();
        int col = coord % 8;
	int row = coord / 8;
        for (int i : this->moveOffsets) {
                destCoordinate = coord + i;
                while (destCoordinate >= 0 && destCoordinate <= 63) {
			int destCol = destCoordinate % 8;
                        if (col == 0 && (i == -9 || i == 7 || i == -1)) {
                                destCoordinate += i;
				continue;
                        }
                        if (col == 7 && (i == 9 || i == -7 || i == 1)) {
				destCoordinate += i;
                                continue;
			}
			if (((destCoordinate / 8) != row) && (i == 1 || i == -1)) {
                                break;
                        }
                        // calculate the dest coordinate
                        // if not a valid coordinate
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
                                break;
                        }
                        if (destCol == 0 && (i == -9 || i == 7)) {
                                break;
                        }
                        if (destCol == 7 && (i == 9 || i == -7)){
                                break;
                        }
                        destCoordinate += i;
                }
        }
        if(validMoves.size() > 0 && !(b.getBuilder()->getIsSetup()) && !(b.getBuilder()->getIsMock())){
                std::vector<Move> legalMoves = getLegalMoves(b.getBuilder(), validMoves);
                return legalMoves;
        }
        return validMoves;
}

Queen::~Queen(){}
#endif

