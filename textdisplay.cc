#include <vector>
#include <iostream>
//#include "tile.h"
#include "textdisplay.h"
//#include "tileinfo.h"

using namespace std;
class Tile;

TextDisplay::TextDisplay(){
    vector<vector<char>> temp (GRIDSIZE, vector<char> (GRIDSIZE, '_'));
    this->display = temp;  
}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td){
    for(int i = 0; i < td.GRIDSIZE; ++i){
        out << td.GRIDSIZE - i << " ";
        for(int j = 0; j < td.GRIDSIZE; ++j){
            out << td.display[i][j];
        }
        out << endl;
    }
    out << endl;
    out << "  abcdefgh" << endl;
    return out;
}

void TextDisplay::notify(Subject &whoFrom){
    TileInfo info = whoFrom.getInfo();
    int row = info.coordinate / GRIDSIZE;
    int col = info.coordinate % GRIDSIZE;
    Piece *p = info.piece;
    if(p == nullptr){
	Colour tileColour = info.colour;
        if(tileColour == Colour::White){
	    this->display[row][col] = ' ';
        }
        else{
	    this->display[row][col] = '_';
        }
        return;
    }
    PieceType type = p->getPieceType();
    Colour c = p->getColour();
    if(type == PieceType::K && c == Colour::White){
	this->display[row][col] = 'K';
    }
    else if(type == PieceType::K && c == Colour::Black){
	this->display[row][col] = 'k';
    }
    else if(type == PieceType::Q && c == Colour::White){
        this->display[row][col] = 'Q';
    }
    else if(type == PieceType::Q && c == Colour::Black){
        this->display[row][col] = 'q';
    }
    else if(type == PieceType::N && c == Colour::White){
        this->display[row][col] = 'N';
    }
    else if(type == PieceType::N && c == Colour::Black){
        this->display[row][col] = 'n';
    }
    else if(type == PieceType::B && c == Colour::White){
        this->display[row][col] = 'B';
    }
    else if(type == PieceType::B && c == Colour::Black){
        this->display[row][col] = 'b';
    }
    else if(type == PieceType::R && c == Colour::White){
        this->display[row][col] = 'R';
    }
    else if(type == PieceType::R && c == Colour::Black){
        this->display[row][col] = 'r';
    }
    else if(type == PieceType::P && c == Colour::White){
        this->display[row][col] = 'P';
    }
    else if(type == PieceType::P && c == Colour::Black){
        this->display[row][col] = 'p';
    }
}

TextDisplay::~TextDisplay(){
    for(int i = 0; i < GRIDSIZE; ++i){
        this->display[i].clear();
        this->display[i].shrink_to_fit();
    }
    this->display.clear();
    this->display.shrink_to_fit();
}
