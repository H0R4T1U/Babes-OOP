//
// Created by h on 3/28/24.
//

#ifndef DISCIPLINASERVICE_H
#define DISCIPLINASERVICE_H
#include "Repo.h"
#include "Disciplina.h"
#include <vector>
#include <string>
#include<map>
#include "undo.h"
class DisciplinaService {
	Repo& rep;
	Repo& contractRepo;
	vector<unique_ptr<UndoAction>> undoActions;


public:
	DisciplinaService(Repo& r, Repo& cR)  noexcept :rep{ r }, contractRepo{cR} {};
	DisciplinaService(const DisciplinaService& dS) = delete;
	const vector<Disciplina>& getDisciplineList()const;
	void addDisciplina(const string& denumire, int ore, const string& tip, const string& profesor);
	void modifyDisciplina(const string& denumire, const string& new_denumire, int ore, const string& tip, const string& profesor);
	void deleteDisciplina(const string& denumire);
	Disciplina findDisciplina(const string& denumire) const;
	size_t listSize() const;
	// filtrare dupa producator
	vector<Disciplina> filterByOre(int ore) const;

	// filtrare dupa tip
	vector<Disciplina> filterByProfesor(const string& profesor) const;

	// sortare dupa numarul de inmatriculare
	vector<Disciplina> sortByDenumire(const char& mode) const;

	// sortare dupa tip
	vector<Disciplina> sortByOre(const char& mode) const;

	// sortare dupa producator + model
	vector<Disciplina> sortByProfesorTip(const char& mode) const;
	// CREAZA RAPORT
	map<string, int> report() const;
	// UNDO
	void undo();
	// getter pentru lungimea listei de masini de spalat
	size_t contractSize() const noexcept
	{
		return contractRepo.size();
	}

	// getter pentru lista de discipline din contract
	vector<Disciplina> contractList() const
	{
		return contractRepo.getAll();
	}

	// adaugam o Disciplina noua in contract
	void addDisciplinaContract(const string& denumire);

	// golim contract
	void emptyContract();

	// generam aleatoriu Discipline in contract 
	void populateContract(size_t number);
	void exportCSV(const string& fileName);
	void exportHTML(const string& fileName);

};


void testService();

#endif //DISCIPLINASERVICE_H
