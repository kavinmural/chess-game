#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <vector>
//#include "subject.h"
#include "piece.h"
#include <iostream>
//class Subject;

class TextDisplay:public Observer{
    std::vector<std::vector<char>> display;
    const int GRIDSIZE = 8;
    public:
     TextDisplay();
     ~TextDisplay() override;
     void notify(Subject &whoFrom) override;
     friend std::ostream &operator <<(std::ostream &out, const TextDisplay &td);
};

#endif
