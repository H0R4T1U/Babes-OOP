//
// Created by horatiu on 6/15/24.
//

#ifndef MUZICA2_REPOSITORY_H
#define MUZICA2_REPOSITORY_H

#include <vector>
#include "Melodie.h"

using namespace std;

class Repository {
private:
    // lista melodii
    vector<Melodie> repo;
    // nume fisier
    const string fileName;
public:
    // constructor Repository
    explicit Repository(const string& fileN):fileName{fileN}{};
    // functie incarcare din fisier
    void load();
    // functie salvare in fisier
    void save();
    // getter de size-ul vectorulkui
    size_t getSize();
    // getter vector
    vector<Melodie> getAll();
    void add(Melodie& m);
    // sterge melodia de la pozitia pos
    void remove(size_t pos);
    // gaseste pozitia elementului denumire, -1 daca nu exista
    int find(const string& denumire);

};
// testeaza repository
void testRepository();


#endif //MUZICA2_REPOSITORY_H
