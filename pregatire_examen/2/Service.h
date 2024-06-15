//
// Created by horatiu on 6/14/24.
//

#ifndef INC_2_SERVICE_H
#define INC_2_SERVICE_H


#include "Repository.h"
#include "Observer.h"
class Service: public Observable {
private:
    Repository repo;
public:
    explicit Service(Repository& repo): repo{repo}{};
    size_t size();
    void add(int id, const string& den, const string& tip, int roti);
    void remove(const string& den);
    __int64_t find(const string& den);
    vector<Tractor> sortDen();
    vector<string> tipuri();
};
void testService();

#endif //INC_2_SERVICE_H
