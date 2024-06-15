//
// Created by horatiu on 6/14/24.
//

#ifndef INC_2_OBSERVER_H
#define INC_2_OBSERVER_H

#include <vector>
#include <algorithm>

using namespace std;

class Observer {
public:
    virtual void update() = 0;
};
class Observable{
private:
    vector<Observer*> observers;
public:
    void addObserver(Observer* o){
        observers.push_back(o);
    }
    void removeObserver(Observer* o){
        observers.erase(remove(observers.begin(),observers.end(),o),observers.end());
    }
    void notify(){
        for(auto o : observers){
            o->update();
        }
    }
};

#endif //INC_2_OBSERVER_H
