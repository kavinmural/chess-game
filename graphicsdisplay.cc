#include "graphicsdisplay.h"
#include "tileinfo.h"
#include "piece.h"

using namespace std;

GraphicsDisplay::GraphicsDisplay(){
    this->height = windowSize / GRIDSIZE;
    this->width = windowSize / GRIDSIZE;
    this->window = new Xwindow();
}

GraphicsDisplay::~GraphicsDisplay(){
    delete this->window;
}

void GraphicsDisplay::notify(Subject &whoNotified){
    TileInfo whoFromInfo = whoNotified.getInfo();
    int x = whoFromInfo.coordinate % 8 * this->width;
    int y = whoFromInfo.coordinate / 8 * this->height;
    int tileColour = 0;
    Piece *p = whoFromInfo.piece;
    if(whoFromInfo.colour == Colour::Black){
	tileColour = Xwindow::Black;
    }
    else{
	tileColour = Xwindow::Red;
    }
    this->window->fillRectangle(x, y, this->width, this->height, tileColour);
    if(p != nullptr){
	PieceType type = p->getPieceType();
	Colour c = p->getColour();
 	if(type == PieceType::K && c == Colour::White){
        	this->window->drawString(x+30, y+35, "K", 0);
    	}
    	else if(type == PieceType::K && c == Colour::Black){
        	this->window->drawString(x+30, y+35, "k", 0);
    	}
    	else if(type == PieceType::Q && c == Colour::White){
        	this->window->drawString(x+30, y+35, "Q", 0);
    	}
    	else if(type == PieceType::Q && c == Colour::Black){
        	this->window->drawString(x+30, y+35, "q", 0);
    	}
    	else if(type == PieceType::N && c == Colour::White){
        	this->window->drawString(x+30, y+35, "N", 0);
    	}
    	else if(type == PieceType::N && c == Colour::Black){
        	this->window->drawString(x+30, y+35, "n", 0);
    	}	
    	else if(type == PieceType::B && c == Colour::White){
        	this->window->drawString(x+30, y+35, "B", 0);
    	}
    	else if(type == PieceType::B && c == Colour::Black){
        	this->window->drawString(x+30, y+35, "b", 0);
    	}
    	else if(type == PieceType::R && c == Colour::White){
        	this->window->drawString(x+30, y+35, "R", 0);
    	}
    	else if(type == PieceType::R && c == Colour::Black){
        	this->window->drawString(x+30, y+35, "r", 0);
    	}
    	else if(type == PieceType::P && c == Colour::White){
        	this->window->drawString(x+30, y+35, "P", 0);
    	}
    	else if(type == PieceType::P && c == Colour::Black){
        	this->window->drawString(x+30, y+35, "p", 0);
    	}
    }
}
