//
// Created by h on 3/28/24.
//

#ifndef DISCIPLINASERVICE_H
#define DISCIPLINASERVICE_H
#include "Repo.h"



class DisciplinaService {
    Repo& rep;

public:
    DisciplinaService(Repo& r)  noexcept :rep{ r } {};
    DisciplinaService(const DisciplinaService& dS) = delete;
    const VectorDinamic<Disciplina>& getDisciplineList()const;
    void addDisciplina(const string& denumire, int ore, const string& tip, const string& profesor);
    void modifyDisciplina(const string& denumire, const string& new_denumire, int ore, const string& tip, const string& profesor);
    void deleteDisciplina(const string& denumire);
    Disciplina findDisciplina(const string& denumire) const;
    size_t listSize() const;
	// filtrare dupa producator
	VectorDinamic<Disciplina> filterByOre(int ore) const;

	// filtrare dupa tip
	VectorDinamic<Disciplina> filterByProfesor(const string& profesor) const;

	// sortare dupa numarul de inmatriculare
	VectorDinamic<Disciplina> sortByDenumire(const char& mode) const;

	// sortare dupa tip
	VectorDinamic<Disciplina> sortByOre(const char& mode) const;

	// sortare dupa producator + model
	VectorDinamic<Disciplina> sortByProfesorTip(const char& mode) const;

};


void testService();

#endif //DISCIPLINASERVICE_H
