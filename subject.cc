#include "subject.h"

void Subject::attach(Observer *o){
    this->observers.emplace_back(o);
}

void Subject::detach(){
    this->observers.pop_back();
}

void Subject::notifyObservers(){
    for(auto &ob : observers) ob->notify(*this);
}
