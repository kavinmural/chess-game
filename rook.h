#ifndef ROOK_H
#define ROOK_H
#include <vector>
#include "piece.h"

class Rook : public Piece {
        public:
        Rook(Colour colour, int coordinate) :
                        Piece{colour, PieceType::R, coordinate, {-8, -1, 1, 8}} {}
                std::vector<Move> getValidMoves(Board& b);
	~Rook()override;
};

std::vector<Move> Rook::getValidMoves(Board& b) {
        std::vector<Move> validMoves;
        int destCoordinate = 0;
        int coord = this->getCoordinate();
        int row = coord / 8;
        int col = coord % 8;
        for (int i : this->moveOffsets) {
                destCoordinate = coord + i;
                while (destCoordinate >= 0 && destCoordinate <= 63) {
                        if (col == 0 && i == -1) {
                                destCoordinate += i;
                                continue;
                        }
                        else if (col == 7 && i == 1) {
                                destCoordinate += i;
                                continue;
                        }
                        if (((destCoordinate / 8) != row) && (i == 1 || i == -1)) {
                                break;
                        }
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
                        destCoordinate += i;
                }
        }
        if(validMoves.size() > 0 && !(b.getBuilder()->getIsSetup()) && !(b.getBuilder()->getIsMock())){
                std::vector<Move> legalMoves = getLegalMoves(b.getBuilder(), validMoves);
                return legalMoves;
        }
        return validMoves;
}

Rook::~Rook(){}
#endif

