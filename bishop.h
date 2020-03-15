#ifndef BISHOP_H
#define BISHOP_H
#include <vector>
#include "piece.h"

class Bishop : public Piece {
	public:
        Bishop(Colour colour, int coordinate)
			: Piece{colour, PieceType::B, coordinate,{-9, -7, 7, 9}} {}
	std::vector<Move> getValidMoves(Board& b);
	~Bishop()override;
};

std::vector<Move> Bishop::getValidMoves(Board& b) {
        std::vector<Move> validMoves;
        int destCoordinate = 0;
        int coord = this->getCoordinate();
        int col = coord % 8;
        for (int i : this->moveOffsets) {
                destCoordinate = coord + i;
                while (destCoordinate >= 0 && destCoordinate <= 63) {
			int destCol = destCoordinate % 8;
                        if (col == 0 && (i == -9 || i == 7)) {
				destCoordinate += i;
                                continue;
                        }
                        if (col == 7 && (i == 9 || i == -7)){
				destCoordinate += i;
				continue;
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
				//destCoordinate += i;
                                break;
                        }
                        if (destCol == 0 && (i == -9 || i == 7)) {
                                //destCoordinate += i;
                                break;
                        }
                        if (destCol == 7 && (i == 9 || i == -7)){
                                //destCoordinate += i;
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

Bishop::~Bishop(){}
#endif
