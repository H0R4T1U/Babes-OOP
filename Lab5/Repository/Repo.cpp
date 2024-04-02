//
// Created by h on 3/28/24.
//

#include "Repo.h"

#include <cassert>


int Repo::store(const Disciplina& d) {
    if(exist(d)) {
        return 0;
    }
    all.push_back(d);
    return 1;
}

bool Repo::exist(const Disciplina& d) const {
        if(find(d.getDenumire()) == -1) return false;
        return true;

}
void Repo::remove(const int& position) {
    all.erase(all.begin() + position);
}

void Repo::modify(const int &position, const Disciplina &disciplina) {
    all[position] = disciplina;
}


int Repo::find(const string& denumire)const {
    for (int i = 0; i < all.size(); i++)
        if (all[i].getDenumire() == denumire)
            return i;
    return -1;
}
size_t Repo::size() const
{
    return all.size();
}
vector<Disciplina> Repo::getAll() const noexcept {
    return all;
}



void testRepo()
{
    Disciplina testDisciplina1{ "ASC", 1, "a", "V" };
    Disciplina testDisciplina2{ "OOP", 2, "b", "I" };
    Disciplina testDisciplina3{ "OS", 3, "c", "B" };
    Repo repo;
    repo.store(testDisciplina1);
    repo.store(testDisciplina2);
    assert(repo.store(testDisciplina1) == 0);
    assert (repo.size() == 2);
    assert (repo.getAll()[0].getDenumire() == testDisciplina1.getDenumire());
    assert (repo.getAll()[0].getOre() == testDisciplina1.getOre());
    assert (repo.getAll()[0].getTip() == testDisciplina1.getTip());
    assert (repo.getAll()[0].getProfesor() == testDisciplina1.getProfesor());

    repo.modify(0, testDisciplina3);
    assert (repo.getAll()[0].getDenumire() == testDisciplina3.getDenumire());
    assert (repo.getAll()[0].getOre() == testDisciplina3.getOre());
    assert (repo.getAll()[0].getTip() == testDisciplina3.getTip());
    assert (repo.getAll()[0].getProfesor() == testDisciplina3.getProfesor());

    repo.remove(1);
    assert (repo.size() == 1);

    int position = repo.find(testDisciplina3.getDenumire());
    assert (repo.getAll()[position].getDenumire() == testDisciplina3.getDenumire());
    assert (repo.getAll()[position].getOre() == testDisciplina3.getOre());
    assert (repo.getAll()[position].getTip() == testDisciplina3.getTip());
    assert (repo.getAll()[position].getProfesor() == testDisciplina3.getProfesor());

    position = repo.find("AG");

    assert (position == -1);
}