//
// Created by horatiu on 5/27/24.
//

#ifndef TEST_OBSERVER_H
#define TEST_OBSERVER_H

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
    void addObserver(Observer* obs){
        observers.push_back(obs);
    }
    void removeObserver(Observer* obs){
        observers.erase(remove(observers.begin(),observers.end(),obs),observers.end());
    }
    void notify(){
        for(auto obs: observers){
            obs->update();
        }
    }
};

#endif //TEST_OBSERVER_H
