#ifndef KING_H
#define KING_H
#include <vector>
#include "piece.h"

class King : public Piece {
        public:
                King(Colour colour, int coordinate)
                        : Piece{colour, PieceType:: K,coordinate, {-9, -8, -7, -1, 1, 7, 8, 9, 2, -2}} {}
                std::vector<Move> getValidMoves(Board &b);
				~King();
};

std::vector<Move> King::getValidMoves(Board& b) {
    std::vector<Move> validMoves;
    int destCoordinate = 0;
    int coord = this->getCoordinate();
	int col = coord % 8;
    for (int i : this->moveOffsets) {
		destCoordinate = coord + i;
		if (destCoordinate < 0 || destCoordinate > 63) {
            continue;
        }
		if (col == 0 && ((i == -9)|| (i == -1))) {
			continue;
		}
		if (col == 7 && ((i == -7) || (i == 1))) {
			continue;
		}
		Tile &destTile = b.getTile(destCoordinate);
		// king side castle
		if (i == 2 && this->isFirstMove && coord <= 60) {
			int bCoord = coord + 1;
			Tile &bTile = b.getTile(bCoord);
			int nCoord = coord + 2;
			Tile &nTile = b.getTile(nCoord);
			int rCoord = coord + 3;
			Tile &rTile = b.getTile(rCoord);
			Piece* rookPiece = rTile.getPiece();
			if (!bTile.isOccupied() && !nTile.isOccupied()&&  rookPiece != nullptr && 
			    (rookPiece->getPieceType() == PieceType::R) && rookPiece->isFirstMove) {
				Move valid = Move(coord,destCoordinate);
                        	valid.moveType = MoveType::CastlingK;
				validMoves.push_back(valid);
			}
		} else if (i == -2 && this->isFirstMove && coord >= 4) {
                        int qCoord = coord - 1;
			Tile &qTile = b.getTile(qCoord);
                        int bCoord = coord - 2;
                        Tile &bTile = b.getTile(bCoord);
                        int nCoord = coord - 3;
                        Tile &nTile = b.getTile(nCoord);
                        int rCoord = coord - 4;
                        Tile &rTile = b.getTile(rCoord);
                        Piece* rookPiece = rTile.getPiece();
                        if (!bTile.isOccupied() && !qTile.isOccupied() &&   !nTile.isOccupied()&& rookPiece != nullptr &&
                            (rookPiece->getPieceType() == PieceType::R) && rookPiece->isFirstMove) {
                                Move valid = Move(coord,destCoordinate);
                                valid.moveType = MoveType::CastlingQ;
                                validMoves.push_back(valid);
                        }

		} else if (!destTile.isOccupied()) {
            		Move valid = Move(coord,destCoordinate);
            		validMoves.push_back(valid);
        }
	else if (i != -2 && i != 2) {
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

King::~King(){}
#endif

