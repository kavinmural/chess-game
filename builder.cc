#include <string>
#include "builder.h"
#include "board.h"
#include "piece.h"
using namespace std;

Builder::Builder(bool setup, bool mock) : isSetup{setup},isMock{mock} {}

void Builder::setPiece(Piece *piece) {
	boardConfig[piece->getCoordinate()] = piece;
}

void Builder::removePiece(int coordinate) {
	boardConfig[coordinate] = nullptr;
}

void Builder::setCurrentColour(const Colour currentColour) {
	this->currentColour = currentColour;
}

Board* Builder::build() {
	Board *temp;
	try {
		temp = new Board(this);
	} catch (string& error) {
		throw error;
	}
	return temp;
}

Piece* Builder::getPiece(const int n) {
	return boardConfig[n];
}

bool Builder::getIsSetup() const {
	return this->isSetup;
}

void Builder::setIsSetup(bool setup) {
	this->isSetup = setup;
}

Colour Builder::getCurrentColour() const {
	return currentColour;
}

bool Builder::getIsMock() const{
	return this->isMock;
}

void Builder::setIsMock(bool mock){
	this->isMock = mock;
}

Builder::~Builder(){
	for(int i = 0; i <= 63; ++i){
		this->removePiece(i);
	}
}
