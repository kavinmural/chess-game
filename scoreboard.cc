#include "scoreboard.h"
using namespace std;

ScoreBoard::ScoreBoard():blackScore{0}, whiteScore{0}{}

double ScoreBoard::getBlackScore() const {
    return this->blackScore;
}

double ScoreBoard::getWhiteScore() const {
    return this->whiteScore;
}

void ScoreBoard::incrementBlackScore(double value){
    this->blackScore = this->blackScore + value;
}

void ScoreBoard::incrementWhiteScore(double value){
    this->whiteScore = this->whiteScore + value;
}

ostream& operator<<(ostream& out, const ScoreBoard& scoreboard) {
	cout << "White: " << scoreboard.getWhiteScore() << endl;
	cout << "Black: " << scoreboard.getBlackScore() << endl;
	return out;
}

ScoreBoard::~ScoreBoard(){}
