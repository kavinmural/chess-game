#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#include <iostream>

class ScoreBoard {
    double blackScore;
    double whiteScore;
    public:
    	ScoreBoard();
	~ScoreBoard();
    	double getBlackScore() const;
    	double getWhiteScore() const;
    	void incrementBlackScore(double n);
    	void incrementWhiteScore(double n);
};

std::ostream& operator<<(std::ostream& out, const ScoreBoard &scoreboard);
#endif
