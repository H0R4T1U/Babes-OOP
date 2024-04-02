//
// Created by h on 3/28/24.
//

#include "DisciplinaService.h"

#include <cassert>

using namespace std;

void DisciplinaService::addDisciplina(const string &denumire, int ore, const string &tip, const string &profesor) {
    Disciplina d {denumire,ore,tip,profesor};
    Validator::validate(d);
    rep.store(d);
}

void DisciplinaService::deleteDisciplina(const string &denumire)  {
    const int position = rep.find(denumire);
    rep.remove(position);
}

void DisciplinaService::modifyDisciplina(const string &denumire, const string& new_Denumire,int ore, const string &tip, const string &profesor)  {
    int position = rep.find(denumire);
    Disciplina d {new_Denumire,ore,tip,profesor};
    Validator::validate(d);
    rep.modify(position,d);

}

Disciplina DisciplinaService::findDisciplina(const string &denumire) const {
    const int pos = rep.find(denumire);
    return getDisciplineList()[pos];
}

vector<Disciplina> DisciplinaService::getDisciplineList() const {
    return rep.getAll();
}
size_t DisciplinaService::listSize() const {
    return rep.size();
}



void testService()
{
    Repo repo;
    Validator val;
    DisciplinaService service{ repo,val };

    service.addDisciplina("asc", 3, "a", "V");
    assert (service.getDisciplineList()[0].getDenumire() == "asc");
    assert (service.getDisciplineList()[0].getOre() == 3);
    assert (service.getDisciplineList()[0].getTip() == "a");
    assert (service.getDisciplineList()[0].getProfesor() == "V");

    service.modifyDisciplina("asc", "oop", 2, "b", "I");
    assert (service.getDisciplineList()[0].getDenumire() == "oop");
    assert (service.getDisciplineList()[0].getOre() == 2);
    assert (service.getDisciplineList()[0].getTip() == "b");
    assert (service.getDisciplineList()[0].getProfesor() == "I");

    Disciplina testDisciplina = {"",-5,"",""};
    testDisciplina = service.findDisciplina("oop");
    assert (testDisciplina.getDenumire() == "oop");
    assert (testDisciplina.getTip() == "b");
    assert (testDisciplina.getProfesor() == "I");

    service.deleteDisciplina("oop");
    try {
        service.addDisciplina("",-1,"","");

    }catch(std::invalid_argument&) {
        assert(true);
    }


    assert (service.listSize() == 0);
}