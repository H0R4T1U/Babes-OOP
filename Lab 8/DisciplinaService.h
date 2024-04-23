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

class DisciplinaService {
    Repo& rep;

public:
    DisciplinaService(Repo& r)  noexcept :rep{ r } {};
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
	map<string, int> report() const;
};
class ContractService
{
private:

	// service-ul pentru masini
	DisciplinaService& disciplinaService;

	// repository-ul pentru masinile de spalat
	Repo contractRepo;

public:

	// constructorul clasei WashService
	ContractService(DisciplinaService& cS) noexcept : disciplinaService{ cS }, contractRepo{} {};

	// getter pentru lungimea listei de masini de spalat
	size_t contractSize() const noexcept
	{
		return contractRepo.size();
	}

	// getter pentru lista de masini de spalat
	vector<Disciplina> contractList() const
	{
		return contractRepo.getAll();
	}

	// adaugam o masina noua in lista de spalat
	void addDisciplina(const string& denumire);

	// golim lista de masini de spalat
	void emptyContract();

	// generam aleatoriu masini care sa fie spalate 
	void populateContract(size_t number);
	void exportContract();
	// impiedicam crearea de noi obiecte de tip Service
	ContractService(const ContractService& wS) = delete;

};

void testService();

#endif //DISCIPLINASERVICE_H
