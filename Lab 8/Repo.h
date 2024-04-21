//
// Created by h on 3/28/24.
//

#ifndef REPO_H
#define REPO_H

#include <string>
#include <vector>
#include "Disciplina.h"
using namespace std;

class Repo {
    vector<Disciplina> all;
public:
    // constructor clasa
    Repo() = default;
    //nu permitem copierea de obiecte
    Repo(const Repo& ot) = delete;
    // adaugarea unei disciplini in vector
    void store(const Disciplina& d);
    // stergerea unei disciplini din vector
    void remove(const int&);
    // Modificarea unei disciplini din vector
    void modify(const int& position, const Disciplina& disciplina);
    // cautarea unei masini in vector
    __int64 find(const string& denumire) const;
    // getter pentru lista curenta de discipline
    const vector<Disciplina>& getAll() const noexcept;
    // getter pentru lungimea listei
    size_t size()const;
};




void testRepo();
#endif //REPO_H
