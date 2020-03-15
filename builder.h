#ifndef BUILDER_H
#define BUILDER_H
#include <map>
#include "colour.h"

class Piece;
class Board;

class Builder {
	std::map<int, Piece*> boardConfig;
	Colour currentColour;
	bool isSetup;
	bool isMock;
	
	public:
		Builder(bool setup, bool mock);
		~Builder();
		void setPiece(Piece* piece);
		void removePiece(int coordinate);
		void setCurrentColour(const Colour currentColour);
		Board* build();
		Piece* getPiece(const int n);
		bool getIsSetup() const;
		void setIsSetup(bool setup);
		bool getIsMock() const;
		void setIsMock(bool mock);
		Colour getCurrentColour() const;
};
#endif
