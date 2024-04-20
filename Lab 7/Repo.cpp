//
// Created by h on 3/28/24.
//

#include "Repo.h"

#include <cassert>


int Repo::store(const Disciplina& d) {
    if (exist(d)) {
        return 0;
    }
    all.add(d);
    return 1;
}

bool Repo::exist(const Disciplina& d) const {
    if (find(d.getDenumire()) == (size_t)-1) return false;
    return true;

}
void Repo::remove(const int& position) {
    all.remove(position);
}

void Repo::modify(const int& position, const Disciplina& disciplina) {
    all.set(position, disciplina);
}


int Repo::find(const string& denumire)const {
    Iterator<Disciplina> it{ all };
    while (it.valid()) {
        if (it.element().getDenumire() == denumire)
            return it.getPoz();
        it.next();
    }
    return -1;
}
size_t Repo::size() const
{
    return all.size();
}
const VectorDinamic<Disciplina>& Repo::getAll() const noexcept {
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
    assert(repo.size() == 2);
    assert(repo.getAll().get(0).getDenumire() == testDisciplina1.getDenumire());
    assert(repo.getAll().get(0).getOre() == testDisciplina1.getOre());
    assert(repo.getAll().get(0).getTip() == testDisciplina1.getTip());
    assert(repo.getAll().get(0).getProfesor() == testDisciplina1.getProfesor());

    repo.modify(0, testDisciplina3);
    assert(repo.getAll().get(0).getDenumire() == testDisciplina3.getDenumire());
    assert(repo.getAll().get(0).getOre() == testDisciplina3.getOre());
    assert(repo.getAll().get(0).getTip() == testDisciplina3.getTip());
    assert(repo.getAll().get(0).getProfesor() == testDisciplina3.getProfesor());

    repo.remove(1);
    assert(repo.size() == 1);

    int position = repo.find(testDisciplina3.getDenumire());
    assert(repo.getAll().get(position).getDenumire() == testDisciplina3.getDenumire());
    assert(repo.getAll().get(position).getOre() == testDisciplina3.getOre());
    assert(repo.getAll().get(position).getTip() == testDisciplina3.getTip());
    assert(repo.getAll().get(position).getProfesor() == testDisciplina3.getProfesor());

    position = repo.find("AG");

    assert(position == -1);
}