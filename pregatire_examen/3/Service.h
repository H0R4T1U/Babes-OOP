//
// Created by horatiu on 6/14/24.
//

#ifndef INC_3_SERVICE_H
#define INC_3_SERVICE_H


#include "Repository.h"
#include "Observer.h"

class Service: public Observable {
private:
    Repository& repo;
public:
    explicit Service(Repository& repo): repo{repo}{};
    void add(int id, const string& denumire, const string& tip, double pret);
    vector<Produs> filterPret(double pret);
    vector<Produs> sortPret();
    size_t size();
    vector<string> tipuri();
    int nrProdTip(const string& tip);
    void validate(const vector<Produs>& vector1, int id, const string &den, const string &tip, double pret);
};

void testService();
#endif //INC_3_SERVICE_H
