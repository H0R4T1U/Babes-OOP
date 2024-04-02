//
// Created by h on 3/28/24.
//

#ifndef REPO_H
#define REPO_H
#include <vector>
#include <string>

#include "../Domain/Disciplina.h"
using namespace std;

class Repo {
    vector<Disciplina> all;
    [[nodiscard]] bool exist(const Disciplina& d) const;
public:
    Repo() = default;
    //nu permitem copierea de obiecte
    Repo(const Repo& ot) = delete;
    int store(const Disciplina& d);
    void remove(const int&);
    void modify(const int& position, const Disciplina& disciplina);
    [[nodiscard]] int find(const string& denumire) const;
    [[nodiscard]] vector<Disciplina> getAll() const noexcept;
    [[nodiscard]] size_t size()const;
};




void testRepo();
#endif //REPO_H
