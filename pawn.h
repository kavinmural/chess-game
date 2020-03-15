#ifndef PAWN_H
#define PAWN_H
#include <vector>
#include <iostream>
#include "piece.h"

class Pawn : public Piece {
	public:
        Pawn(Colour colour, int coordinate)
			: Piece{colour, PieceType::P, coordinate, {8, 16, 7, 9, 1, -1}} {}
		std::vector<Move> getValidMoves(Board& b);
        ~Pawn()override;
};

std::vector<Move> Pawn::getValidMoves(Board& b) {
        std::vector<Move> validMoves;
        int destCoordinate = 0;
        int coord = this->getCoordinate();
        Colour colour = this->getColour();
        // offset multiplier is required for directional movement for pawn
        int offsetMultiplier = 1;
        if (colour == Colour::White) {
                offsetMultiplier *= -1;
        }
        for (int i : this->moveOffsets) {
                int col = coord % 8;
                i *= offsetMultiplier;
                destCoordinate = coord + i;
                if (destCoordinate < 0 || destCoordinate > 63) {
                        continue;
                }
                Tile &destTile = b.getTile(destCoordinate);
                Piece* destPiece = destTile.getPiece();
		if ((i == 7 || i == 9 || i == -7 || i == -9) && !destTile.isOccupied()) {
			if (colour == Colour::Black) {
				int backCoord = destCoordinate - 8;
				if (backCoord > 63 || backCoord < 0) continue;
                        	Tile &backTile = b.getTile(backCoord);
				Piece* backPiece = backTile.getPiece();
                        	if (backTile.isOccupied() && (backPiece->getPieceType() == PieceType::P) && 
				    (backPiece->getColour() != colour) && backPiece->isSecondMove) {
                                	Move valid = Move(coord,destCoordinate);
                                	valid.moveType = MoveType::EnPassant;
					validMoves.push_back(valid);
                        	}
			}
			else {
				int backCoord = destCoordinate + 8;
				if (backCoord > 63 || backCoord < 0) continue;
                                Tile &backTile = b.getTile(backCoord);
                                Piece* backPiece = backTile.getPiece();
                                if (backTile.isOccupied() && (backPiece->getPieceType() == PieceType::P) &&
                                    (backPiece->getColour() != colour) && backPiece->isSecondMove) {
					Move valid = Move(coord,destCoordinate);
                                        valid.moveType = MoveType::EnPassant;
                                        validMoves.push_back(valid);
                                }				
			}
		}
                else if (!destTile.isOccupied() && (i == 8 || i == -8)) {
                        Move valid = Move(coord,destCoordinate);
			int destRow = destCoordinate / 8;
			if((colour == Colour::Black && destRow == 7) || (colour == Colour::White && destRow == 0)){
				valid.moveType = MoveType::Promotion;
			}
                       	validMoves.push_back(valid);
                }
                else if ((i == 16 || i == -16) && this->isFirstMove == true) {
                        int inBetweenCoord = coord + (i/2);
                        Tile &inBetweenTile = b.getTile(inBetweenCoord);
                        if (!inBetweenTile.isOccupied() && !destTile.isOccupied()) {
                                Move valid = Move(coord,destCoordinate);
                                validMoves.push_back(valid);
                        }
                }                
                else if (i == 7 || i == -7) {
                        if (destPiece == nullptr) {
                                continue;
                        }
                        else {
                                if ((col == 7 && colour == Colour::White) || (col == 0 && colour == Colour::Black) ||
                                (destPiece->getColour() == colour)) {
                                        continue;
                                }
                                else {
                                        Move valid = Move(coord,destCoordinate);
					valid.moveType = MoveType::Capture;
					int destRow = destCoordinate / 8;
		                        if((colour == Colour::Black && destRow == 7) || (colour == Colour::White && destRow == 0)){
                		                valid.moveType = MoveType::Promotion;
                        		}
                                        validMoves.push_back(valid);    
                                }
                        }
                }
                else if (i == 9 || i == -9) {
                        if (destPiece == nullptr) {
                                continue;
                        }
                        else {
                                if ((col == 0 && colour == Colour::White) || (col == 7 && colour == Colour::Black) ||
                                (destPiece->getColour() == colour)) {
                                        continue;
                                }
                                else {
                                        Move valid = Move(coord,destCoordinate);
					valid.moveType = MoveType::Capture;
					int destRow = destCoordinate / 8;
                                        if((colour == Colour::Black && destRow == 7) || (colour == Colour::White && destRow == 0)){
                                                valid.moveType = MoveType::Promotion;
                                        }
                                        validMoves.push_back(valid);    
                                }
                        }
                }
        }
        if(validMoves.size() > 0 && !(b.getBuilder()->getIsSetup()) && !(b.getBuilder()->getIsMock())){
                std::vector<Move> legalMoves = getLegalMoves(b.getBuilder(), validMoves);
                return legalMoves;
        }
        return validMoves;
}

Pawn::~Pawn(){}
#endif

