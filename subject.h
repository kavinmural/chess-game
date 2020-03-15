#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include "tileinfo.h"
#include "observer.h"

class Observer;
class Tile;

class Subject{
    std::vector<Observer*> observers;
    public:
     void attach(Observer *o);
     void detach();
     void notifyObservers();
     virtual TileInfo getInfo() const = 0;
};
#endif
