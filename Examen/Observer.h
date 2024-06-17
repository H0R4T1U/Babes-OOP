//
// Created by horatiu on 6/16/24.
//

#ifndef EXAMEN_OBSERVER_H
#define EXAMEN_OBSERVER_H

#include <vector>
#include <algorithm>
using namespace std;
class Observer {
public:
    // functia update pur virtuala
    virtual void update() = 0;
};
class Observable{
private:
    vector<Observer*> obs;
public:
    // adauga observer
    void addObserver(Observer* o){
        obs.push_back(o);
    }
    // sterge observer
    void deleteObserver(Observer* o){
        obs.erase(remove(obs.begin(),obs.end(),o),obs.end());
    }
    // notifica observeri de schimbare
    void notify(){
        for(auto* o : obs){
            o->update();
        }
    }

};

#endif //EXAMEN_OBSERVER_H
