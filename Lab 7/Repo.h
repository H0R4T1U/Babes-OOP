//
// Created by h on 3/28/24.
//

#ifndef REPO_H
#define REPO_H

#include <string>
#include "MyVector.h"
#include "Disciplina.h"
using namespace std;

class Repo {
    VectorDinamic<Disciplina> all;
    bool exist(const Disciplina& d) const;
public:
    Repo() = default;
    //nu permitem copierea de obiecte
    Repo(const Repo& ot) = delete;
    int store(const Disciplina& d);
    void remove(const int&);
    void modify(const int& position, const Disciplina& disciplina);
    int find(const string& denumire) const;
    const VectorDinamic<Disciplina>& getAll() const noexcept;
    size_t size()const;
};




void testRepo();
#endif //REPO_H
