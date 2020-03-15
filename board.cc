#include <iostream>
#include <string>
#include "board.h"
#include "builder.h"
#include "rook.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include "pawn.h"
#include "knight.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
using namespace std;

vector<Piece*> Board::getActivePieces(Colour colour) {
	vector<Piece*> activePieces;
	for (Subject& tile : board) {
		TileInfo info = tile.getInfo();
		Piece* p = info.piece;

		if (p != nullptr && p->getColour() == colour) {
			activePieces.emplace_back(p);
		}
	}
	return activePieces;
}

vector<Move> Board::getValidMoves(Colour colour) {
	vector<Move> validMoves;
	vector<Piece*> pieces;
	if (colour == Colour::White) pieces = whitePieces;
	else pieces = blackPieces;
	for (Piece* p : pieces) {
		vector<Move> pieceValidMoves = p->getValidMoves(*this);
		//cout << "num of moves: " << pieceValidMoves.size() << " color: " << colour<< endl;
		if(pieceValidMoves.size() > 0){
			validMoves.insert(validMoves.end(), pieceValidMoves.begin(), pieceValidMoves.end());
		}
	}
	return validMoves;
}

vector<Tile> Board::createBoard(Builder* builder) {
	this->td = new TextDisplay();
	currentColour = builder->getCurrentColour();
	if (!builder->getIsSetup() && !builder->getIsMock()) this->obGraphics = new GraphicsDisplay();
	vector<Tile> board;
	for (int i = 0; i <= GRID_SIZE; i++) {
		const int row = i / 8;
		const int col = i % 8;
		Colour tileColour;

		if (row % 2 == 0) {
			if (col % 2 == 0) tileColour = Colour::White;
			else tileColour = Colour::Black;
		} else {
			if (col % 2 == 0) tileColour = Colour::Black;
			else tileColour = Colour::White;
		}
		
		Tile tile = Tile(i, tileColour, builder->getPiece(i));
		tile.attach(td);
        if (!builder->getIsSetup() && !builder->getIsMock()) tile.attach(obGraphics);
	tile.notifyObservers();
	board.emplace_back(tile);
	}

	return board;
}

Board* Board::createStandardBoard() {
	Builder* builder = new Builder(false, false);

	builder->setPiece(new Rook(Colour::Black, 0));
	builder->setPiece(new Knight(Colour::Black, 1));
	builder->setPiece(new Bishop(Colour::Black, 2));
	builder->setPiece(new Queen(Colour::Black, 3));
	builder->setPiece(new King(Colour::Black, 4));
	builder->setPiece(new Bishop(Colour::Black, 5));
	builder->setPiece(new Knight(Colour::Black, 6));
	builder->setPiece(new Rook(Colour::Black, 7));
	builder->setPiece(new Pawn(Colour::Black, 8));
	builder->setPiece(new Pawn(Colour::Black, 9));
	builder->setPiece(new Pawn(Colour::Black, 10));
	builder->setPiece(new Pawn(Colour::Black, 11));
	builder->setPiece(new Pawn(Colour::Black, 12));
	builder->setPiece(new Pawn(Colour::Black, 13));
	builder->setPiece(new Pawn(Colour::Black, 14));
	builder->setPiece(new Pawn(Colour::Black, 15));

	builder->setPiece(new Pawn(Colour::White, 48));
	builder->setPiece(new Pawn(Colour::White, 49));
	builder->setPiece(new Pawn(Colour::White, 50));
	builder->setPiece(new Pawn(Colour::White, 51));
	builder->setPiece(new Pawn(Colour::White, 52));
	builder->setPiece(new Pawn(Colour::White, 53));
	builder->setPiece(new Pawn(Colour::White, 54));
	builder->setPiece(new Pawn(Colour::White, 55));
	builder->setPiece(new Rook(Colour::White, 56));
	builder->setPiece(new Knight(Colour::White, 57));
	builder->setPiece(new Bishop(Colour::White, 58));
	builder->setPiece(new Queen(Colour::White, 59));
	builder->setPiece(new King(Colour::White, 60));
	builder->setPiece(new Bishop(Colour::White, 61));
	builder->setPiece(new Knight(Colour::White, 62));
	builder->setPiece(new Rook(Colour::White, 63));

	builder->setCurrentColour(Colour::White);

	return builder->build();
}

bool Board::canMove(vector<Move> moves, Move &userMove) {
	for (Move& m : moves) {
		if (m.oldCoord == userMove.oldCoord && m.newCoord == userMove.newCoord){
			userMove.moveType = m.moveType;
			return true;
		}
		//cout << m.oldCoord << " " << m.newCoord << endl;
	}

	return false;
}

void Board::makeMove(Move m) {
	vector<Move> moves;
	bool check = false;
	if (currentColour == Colour::White) {
		moves = whiteValidMoves;
	} else moves = blackValidMoves;	

	if (canMove(moves, m) == true) {
		check = true;
		int oldCoordinate = m.oldCoord;
		int newCoordinate = m.newCoord;
		Piece* attackingPiece = board[oldCoordinate].getPiece();
		Piece* oldPiece = board[newCoordinate].getPiece();
		// if there is a piece at the square, delete it
		if (oldPiece != nullptr){
			delete oldPiece;
			board[newCoordinate].setPiece(nullptr);
			this->builder->removePiece(newCoordinate);
		}

		// check if move is a pawn promotion or castle
		if (m.moveType == MoveType::CastlingK) {
			int rookOldCoordinate = oldCoordinate + 3;
			int rookNewCoordinate = newCoordinate - 1;
			Piece *rook = this->board[rookOldCoordinate].getPiece();
			rook->setCoordinate(rookNewCoordinate);
                        board[rookNewCoordinate].setPiece(rook);
                        board[rookOldCoordinate].setPiece(nullptr);
                        this->builder->removePiece(rookOldCoordinate);
                        this->builder->setPiece(rook);
			board[rookOldCoordinate].notifyObservers();
			board[rookNewCoordinate].notifyObservers();

		}
		else if (m.moveType == MoveType::CastlingQ) {
			int rookOldCoordinate = oldCoordinate - 4;
                        int rookNewCoordinate = newCoordinate + 1;
                        Piece *rook = this->board[rookOldCoordinate].getPiece();
                        rook->setCoordinate(rookNewCoordinate);
                        board[rookNewCoordinate].setPiece(rook);
                        board[rookOldCoordinate].setPiece(nullptr);
                        this->builder->removePiece(rookOldCoordinate);
                        this->builder->setPiece(rook);
                        board[rookOldCoordinate].notifyObservers();
                        board[rookNewCoordinate].notifyObservers();

                }
		else if (m.moveType == MoveType::EnPassant) {
			if (currentColour == Colour::Black) {
				int coordinate = newCoordinate - 8;
				Piece *deletePiece = this->board[coordinate].getPiece();
				if (deletePiece != nullptr) {
					delete deletePiece;
					this->builder->removePiece(coordinate);
					board[coordinate].setPiece(nullptr);
					board[coordinate].notifyObservers();
				}
			}
			else {
				int coordinate = newCoordinate + 8;
                                Piece *deletePiece = this->board[coordinate].getPiece();
                                if (deletePiece != nullptr) {
					delete deletePiece;
                                        this->builder->removePiece(coordinate);
                                        board[coordinate].setPiece(nullptr);
					 board[coordinate].notifyObservers();
                                }

			}
			//Set Board & Builder

		}
		else if (m.moveType == MoveType::Promotion) {
			char piece;
			cin >> piece;

			delete board[oldCoordinate].getPiece();
			Piece* piecePointer;

			if (piece == 'q') {
				piecePointer = new Queen(Colour::Black, newCoordinate);
			} else if (piece == 'Q') {
				piecePointer = new Queen(Colour::White, newCoordinate);
			} else if (piece == 'b') {
				piecePointer = new Bishop(Colour::Black, newCoordinate);
			} else if (piece == 'B') {
				piecePointer = new Bishop(Colour::White, newCoordinate);
			} else if (piece == 'n') {
				piecePointer = new Knight(Colour::Black, newCoordinate);
			} else if (piece == 'N') {
				piecePointer = new Knight(Colour::White, newCoordinate);	
			} else if (piece == 'r') {
				piecePointer = new Rook(Colour::Black, newCoordinate);
			} else if (piece == 'R') {
				piecePointer = new Rook(Colour::White, newCoordinate);
			}

			//builder->removePiece(oldCoordinate);
			attackingPiece = piecePointer;
			//builder->setPiece(piecePointer);
		} 	//Set Board & Builder
			attackingPiece->setCoordinate(newCoordinate);
			board[newCoordinate].setPiece(attackingPiece);
			board[oldCoordinate].setPiece(nullptr);
			this->builder->removePiece(oldCoordinate);
			this->builder->setPiece(attackingPiece);

			if (attackingPiece->isFirstMove) {
				attackingPiece->isFirstMove = false;
				attackingPiece->isSecondMove = true;
			}
			else if (attackingPiece->isSecondMove) {
				attackingPiece->isSecondMove = false;
			}
	

		board[oldCoordinate].notifyObservers();
		board[newCoordinate].notifyObservers();

		if (currentColour == Colour::White) currentColour = Colour::Black;
		else currentColour = Colour::White;
		whitePieces = getActivePieces(Colour::White);
		blackPieces = getActivePieces(Colour::Black);
		whiteValidMoves = getValidMoves(Colour::White);
		blackValidMoves = getValidMoves(Colour::Black);
	}
	// do end game checks
	if (currentColour == Colour::White) moves = whiteValidMoves;
	else moves = blackValidMoves;
	
	string error;
	if (moves.size() == 0 && isCheck(currentColour)) {
		error = "checkmate";
		throw error;
	} else if (moves.size() == 0 && !isCheck(currentColour)) {
		error = "stalemate";
		throw error;
	} else if (check == false){
		error = "illegal";
		throw error;
	}
	else if (isCheck(currentColour)){
		error = "check";
		throw error;
	}
}

Board::Board(Builder* builder)
	: builder{builder}, board{createBoard(builder)},
		whitePieces{getActivePieces(Colour::White)},
		blackPieces{getActivePieces(Colour::Black)},
		whiteValidMoves{getValidMoves(Colour::White)},
		blackValidMoves{getValidMoves(Colour::Black)}
{
	//Avoid MoveType
	for(Move m : whiteValidMoves){
		for(Move m2 : blackValidMoves){
			if(m2.newCoord == m.oldCoord){
                                m.moveType = MoveType::Avoid;
                        }
		}
	}
        for(Move m : blackValidMoves){
                for(Move m2 : whiteValidMoves){
                        if(m2.newCoord == m.oldCoord){
                                m.moveType = MoveType::Avoid;
                        }
                }
        }
	//Avoid MoveType
	if (builder->getIsSetup()) {
		// no pawns in first or last
		for (int i = 0; i < 8; i++) {
			Piece* piece = board[i].getPiece();
			
			if (piece != nullptr) {
				PieceType pieceType = piece->getPieceType();
				if (pieceType == PieceType::P) {
					string error = "invalid pawn";
					throw error;
				}
			}
		}
		for (int i = 56; i < 64; i++) {
			Piece* piece = board[i].getPiece();
			
			if (piece != nullptr) {
				PieceType pieceType = piece->getPieceType();
				if (pieceType == PieceType::P) {
					string error = "invalid pawn";
					throw error;
				}
			}
		}
		// neither king is in check
		string error;
		if (isCheck(Colour::White)) {
			error = "white king check";
			throw error;
		}

		if (isCheck(Colour::Black)) {
			error = "black king check";
			throw error;
		}
		// only one king for both colours
		bool whiteKingExists = false;
		bool blackKingExists = false;
		for (Tile t : board) {
			Piece* p = t.getPiece();
			if (p == nullptr) continue;
			if (p->getPieceType() == PieceType::K) {
				if (p->getColour() == Colour::White) {
					if (whiteKingExists) {
						error = "more than one white king";
						throw error;
					}
					whiteKingExists = true;
				}

				if (p->getColour() == Colour::Black) {
					if (blackKingExists) {
						error = "more than one black king";
						throw error;
					}
					blackKingExists = true;
				}
			}
		}
		if (!whiteKingExists) {
			error = "white king dne";
			throw error;
		}

		if (!blackKingExists) {
			error = "black king dne";
			throw error;
		}
	}
}

Board::~Board() {
    for(Tile t : this->board){
	t.setPiece(nullptr);	
    }
    this->board.clear();
    this->whiteValidMoves.clear();
    this->blackValidMoves.clear();
	if (!builder->getIsSetup() && !builder->getIsMock()) {
		delete builder;

		for(Piece *p : this->whitePieces){
			delete p;
		}

		for(Piece *p : this->blackPieces){
			delete p;
		}

		delete this->obGraphics;
	}
    this->whitePieces.clear();
    this->blackPieces.clear();
    delete this->td;
}

Tile &Board::getTile(int coordinate) {
	return board.at(coordinate);
}

int Board::findKing(Colour colour) {
	int kingCoordinate = -1;
	for(Subject &tile: this->board){
		TileInfo info = tile.getInfo();
		if(info.piece && info.piece->getColour() == colour && info.piece && info.piece->getPieceType() == PieceType::K){
			kingCoordinate = info.coordinate;
		}
	}

	return kingCoordinate;
}

bool Board::isCheck(Colour colour) {
	int kingIndex = findKing(colour);
	vector<Move> opposingMoves;
	if (colour == Colour::Black) opposingMoves = whiteValidMoves;
	else opposingMoves = blackValidMoves;		

	for (Move m : opposingMoves) {
		if (m.newCoord == kingIndex) return true;
	}

	return false;
}

ostream& operator<<(ostream& out, const Board& board) {
	out << *(board.td);
	return out;
}

Builder* Board::setup() {
	Builder* builder = new Builder(true, false);
	builder->setCurrentColour(Colour::White);
	string setupCommand;

	while (cin >> setupCommand) {
		if (setupCommand == "+") {
			char pieceType;
			string coordinate;

			cin >> pieceType >> coordinate;

			int intCoordinate = ((8 - (coordinate[1] - '0')) * 8) + (coordinate[0] - 'a');
			if (pieceType == 'R') {
				builder->setPiece(new Rook(Colour::White, intCoordinate));
			} else if (pieceType == 'N') {
				builder->setPiece(new Knight(Colour::White, intCoordinate));
			} else if (pieceType == 'B') {
				builder->setPiece(new Bishop(Colour::White, intCoordinate));
			} else if (pieceType == 'Q') {
				builder->setPiece(new Queen(Colour::White, intCoordinate));
			} else if (pieceType == 'K') {
				builder->setPiece(new King(Colour::White, intCoordinate));
			} else if (pieceType == 'P') {
				builder->setPiece(new Pawn(Colour::White, intCoordinate));
			} else if (pieceType == 'r') {
				builder->setPiece(new Rook(Colour::Black, intCoordinate));
			} else if (pieceType == 'n') {
				builder->setPiece(new Knight(Colour::Black, intCoordinate));
			} else if (pieceType == 'b') {
				builder->setPiece(new Bishop(Colour::Black, intCoordinate));
			} else if (pieceType == 'q') {
				builder->setPiece(new Queen(Colour::Black, intCoordinate));
			} else if (pieceType == 'k') {
				builder->setPiece(new King(Colour::Black, intCoordinate));
			} else if (pieceType == 'p') {
				builder->setPiece(new Pawn(Colour::Black, intCoordinate));
			}
		} else if (setupCommand == "-") {
			string coordinate;
			cin >> coordinate;

			int intCoordinate = ((8 - coordinate[1]) * 8) + (coordinate[0] - 97);
			builder->removePiece(intCoordinate);
		} else if (setupCommand == "=") {
			string colour;
			while (cin >> colour) {
				if (colour == "white") {
					builder->setCurrentColour(Colour::White);
					break;
				} else if (colour == "black") {
					builder->setCurrentColour(Colour::Black);
					break;
				} else {
					cout << "Unknown colour, please enter white or black" << endl;
				}
			}
		} else if (setupCommand == "done") {
			break;
		} else {
			cout << "Unknown command. Please try again." << endl;
		}
	}

	return builder;
}

Colour Board::getCurrentColour() {
	return currentColour;
}

Builder* Board::getBuilder() {
	return builder;
}

vector<Move> Board::getMoves(Colour colour) {
	if (colour == Colour::White) {
		return whiteValidMoves;
	}

	return blackValidMoves;
}
