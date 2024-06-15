//
// Created by horatiu on 6/15/24.
//

#ifndef MUZICA2_SERVICE_H
#define MUZICA2_SERVICE_H


#include "Repository.h"
#include <map>
using namespace std;
class Service {
private:
    // repository piese
    Repository& repo;
public:
    // constructor Service
    explicit Service( Repository& repo): repo{repo}{};
    // methoda de validare  a melodiei, returneaza 0 daca este ok , 1 daca nu
    static int validate(const vector<Melodie>& rep,int id,const string& titlu, const string& artist, const string& tip);
    // functie de adaugare in repo
    void add(int id, const string& denumire, const string& artist, const string& tip);
    // functie de stergere din repo
    void remove(const string& titlu);
    // getter de vector din repo
    vector<Melodie> getAll();
    // getter de size repo din vector
    size_t size();
    // functie de sortare dupa artist, returneaza vector de melodii sortat
    vector<Melodie> sortArt();
    // METHODA CE Returneaza nr de tipuri de piese, rock folk etc...
    map<string,int> getNrTypes();
};
// teste service
void testService();


#endif //MUZICA2_SERVICE_H
