#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H
#include <vector>
#include <string>
#include "observer.h"
#include "tile.h"
#include "window.h"
#include "subject.h"

const size_t windowSize = 500;
class Tile;

class GraphicsDisplay:public Observer{
    Xwindow *window;
    const size_t GRIDSIZE = 8;
    int height;
    int width;
    public:
     GraphicsDisplay();
     ~GraphicsDisplay();
     void notify(Subject &whoNotified) override;
};
#endif
