//
// Created by h on 3/28/24.
//

#include "DisciplinaService.h"
#include "disciplinaValidator.h"
#include <cassert>
#include <algorithm>
#include <random>
#include <chrono>
#include "exception.h"
#pragma warning( disable : 4244 )
using namespace std;

void DisciplinaService::addDisciplina(const string& denumire, int ore, const string& tip, const string& profesor) {
    if (rep.find(denumire) >= 0)
        throw ExistentDisciplinaError("Disciplina exista deja in baza de date!\n");
    if (validateDisciplina(denumire, ore, tip, profesor) == 0)
        throw InvalidDisciplinaError("Datele disciplinei sunt invalide\n");
    Disciplina d{ denumire,ore,tip,profesor };
    rep.store(d);
}

void DisciplinaService::deleteDisciplina(const string& denumire) {
	const int position = rep.find(denumire);
	if (position  < 0)
		throw InexistentDisciplinaError("disciplina nu exista in baza de date!\n");
	rep.remove(position);

}

void DisciplinaService::modifyDisciplina(const string& denumire, const string& new_Denumire, int ore, const string& tip, const string& profesor) {
    int position = rep.find(denumire);
    if (position < 0)
        throw InexistentDisciplinaError("disciplina nu exista in baza de date!\n");

	else if(validateDisciplina(new_Denumire, ore, tip, profesor) == 0)
		throw InvalidDisciplinaError("Datele disciplinei sunt invalide!\n");
    Disciplina d{ new_Denumire,ore,tip,profesor };
    rep.modify(position, d);

}

Disciplina DisciplinaService::findDisciplina(const string& denumire) const {
    const int position = rep.find(denumire);
    if (position < 0) {
		throw InexistentDisciplinaError("Disciplina nu exista in baza de date!\n");
    }
    return getDisciplineList().at(position);
}

const vector<Disciplina>& DisciplinaService::getDisciplineList() const {
    return rep.getAll();
}
size_t DisciplinaService::listSize() const {
    return rep.size();
}

vector<Disciplina> DisciplinaService::filterByOre(int ore) const
{

    vector<Disciplina> filteredList;
	copy_if(getDisciplineList().begin(), getDisciplineList().end(), back_inserter(filteredList), [ore](const Disciplina& d) { return d.getOre() == ore; });

	if (filteredList.empty()) {
		throw EmptyListError("Nu exista discipline de acest tip in baza de date! \n");
	}
    return filteredList;
}

vector<Disciplina> DisciplinaService::filterByProfesor(const string& profesor) const
{
	vector<Disciplina> filteredList;
	copy_if(getDisciplineList().begin(), getDisciplineList().end(), back_inserter(filteredList), [profesor](const Disciplina& d) { return d.getProfesor() == profesor; });

	if (filteredList.empty()) {
		throw EmptyListError("Nu exista discipline de acest tip in baza de date! \n");
	}
	return filteredList;
}

vector<Disciplina> DisciplinaService::sortByDenumire(const char& mode) const
{
	vector<Disciplina> sortedList = getDisciplineList();
	if (mode != 'c' && mode != 'd')
		throw InvalidSortingMode("Mod de sortare invalid!\n");
	if (mode == 'c')
		sort(sortedList.begin(), sortedList.end(), [](const Disciplina& d1, const Disciplina& d2) {return d1.getDenumire() < d2.getDenumire(); });
	else
		sort(sortedList.begin(), sortedList.end(), [](const Disciplina& d1, const Disciplina& d2) {return d1.getDenumire() > d2.getDenumire(); });
    return sortedList;
}

vector<Disciplina> DisciplinaService::sortByOre(const char& mode) const
{
	vector<Disciplina> sortedList = getDisciplineList();
	if (mode != 'c' && mode != 'd')
		throw InvalidSortingMode("Mod de sortare invalid!\n");
	if (mode == 'c')
		sort(sortedList.begin(), sortedList.end(), [](const Disciplina& d1, const Disciplina& d2) {return d1.getOre() < d2.getOre(); });
	else
		sort(sortedList.begin(), sortedList.end(), [](const Disciplina& d1, const Disciplina& d2) {return d1.getOre() > d2.getOre(); });
	return sortedList;
}

vector<Disciplina> DisciplinaService::sortByProfesorTip(const char& mode) const
{
    vector<Disciplina> sortedList = getDisciplineList();
	if (mode != 'c' && mode != 'd')
		throw InvalidSortingMode("Mod de sortare invalid!\n");
	if (mode == 'c')
		sort(sortedList.begin(), sortedList.end(), [](const Disciplina& d1, const Disciplina& d2)
			{
				if (d1.getProfesor() == d2.getProfesor())
					return d1.getTip() < d2.getTip();
				else
					return d1.getProfesor() < d2.getProfesor();
			});
	else
		sort(sortedList.begin(), sortedList.end(), [](const Disciplina& d1, const Disciplina& d2)
			{
				if (d1.getProfesor() == d2.getProfesor())
					return d1.getTip() > d2.getTip();
				else
					return d1.getProfesor() > d2.getProfesor();
			});
    return sortedList;

}
map<string, int> DisciplinaService::report() const
{
	map<string, int> report;
	for (auto& d : getDisciplineList())
	{
		auto it = report.find(d.getTip());
		if (it != report.end())
			report[d.getTip()]++;
		else
			report.insert(pair<string, int>(d.getTip(), 1));
	}
	return report;
}
void ContractService::addDisciplina(const string& denumire)
{
	if (validateDenumire(denumire) == 0)
		throw InvalidDenumire("Denumirea disciplinei este invalida!\n");
	try
	{
		Disciplina disciplina = disciplinaService.findDisciplina(denumire);
		contractRepo.store(disciplina);
	}
	catch (const Error& error)
	{
		throw error;
	}
}

void ContractService::emptyContract()
{
	while (contractRepo.size())
		contractRepo.remove(0);
}
void ContractService::populateContract(size_t number)
{
	if (number > disciplinaService.listSize())
		throw InvalidGenerateNumber("Numarul de discipline de generat este prea mare!\n");
	vector<Disciplina> copyDisciplinaList = disciplinaService.getDisciplineList();
	auto seed = chrono::system_clock::now().time_since_epoch().count();
	shuffle(copyDisciplinaList.begin(), copyDisciplinaList.end(), default_random_engine(seed));
	for (size_t i = 0; i < number; i++)
		contractRepo.store(copyDisciplinaList.at(i));
}
void testService()
{
	Repo repo;
	DisciplinaService service{ repo };

	// adaugam cateva DISCIPLINE
	service.addDisciplina("ASC", 30, "FRECVENTA", "VANCEA");
	service.addDisciplina("OOP", 30, "FRECVENTA", "ISTVAN");
	service.addDisciplina("FP", 30, "FRECVENTA", "ISTVAN");
	service.addDisciplina("SO", 30, "FRECVENTA", "BOIAN");
	service.addDisciplina("AG", 30, "FRECVENTA", "SUCIU");

	// incercam sa adaugam o disciplina invalida
	try
	{
		service.addDisciplina("TES1T", -1, "FRECVENTA", "VANCEA");
	}
	catch (const Error& error)
	{
		assert(error.getMessage() == "Datele disciplinei sunt invalide\n");
	}

	// incercam sa adaugam o disciplina deja existenta
	try
	{
		service.addDisciplina("ASC", 30, "CLIO", "ALTELE");
	}
	catch (const Error& error)
	{
		assert(error.getMessage() == "Disciplina exista deja in baza de date!\n");
	}

	// verificam ca s-au adaugat disciplinele valide
	assert(service.getDisciplineList().at(0).getDenumire() == "ASC");
	assert(service.getDisciplineList().at(0).getOre() == 30);
	assert(service.getDisciplineList().at(0).getTip() == "FRECVENTA");
	assert(service.getDisciplineList().at(0).getProfesor() == "VANCEA");

	// verificam ca s-a modificat disciplina
	service.modifyDisciplina("ASC", "csa", 35, "Freq", "vancea");
	assert(service.getDisciplineList().at(0).getDenumire() == "csa");
	assert(service.getDisciplineList().at(0).getOre() == 35);
	assert(service.getDisciplineList().at(0).getTip() == "Freq");
	assert(service.getDisciplineList().at(0).getProfesor() == "vancea");

	// incercam sa modificam o disciplina inexistenta
	try
	{
		service.modifyDisciplina("asdf", "asdf", 55, "frecv", "xxx");
	}
	catch (const Error& error)
	{
		assert(error.getMessage() == "disciplina nu exista in baza de date!\n");
	}

	try
	{
		service.modifyDisciplina("FP", "asc1", -5, "TEST", "TEST");
	}
	catch (const Error& error)
	{
		assert(error.getMessage() == "Datele disciplinei sunt invalide!\n");
	}

	// cautam o disciplina existenta
	Disciplina testDisciplina;
	testDisciplina = service.findDisciplina("FP");
	assert(testDisciplina.getDenumire() == "FP");
	assert(testDisciplina.getOre() == 30);
	assert(testDisciplina.getTip() == "FRECVENTA");
	assert(testDisciplina.getProfesor() == "ISTVAN");

	// cautam o disciplina inexistenta
	try
	{
		testDisciplina = service.findDisciplina("ASDF");
	}
	catch (const Error& error)
	{
		assert(error.getMessage() == "Disciplina nu exista in baza de date!\n");
	}

	// stergem o disciplina si verificam ca s-a micsorat marimea
	service.deleteDisciplina("FP");
	assert(service.listSize() == 4);

	// incercam sa stergem o disciplina inexistenta
	try
	{
		service.deleteDisciplina("ASDF");
	}
	catch (const Error& error)
	{
		assert(error.getMessage() == "disciplina nu exista in baza de date!\n");
	}


	// teste pentru filtrarea dupa ore
	// testam cu ore existente
	vector<Disciplina> disciplinaList = service.filterByOre(35);
	assert(disciplinaList.size() == 1);
	assert(disciplinaList.at(0).getDenumire() == "csa");
	assert(disciplinaList.at(0).getOre() == 35);
	assert(disciplinaList.at(0).getTip() == "Freq");
	assert(disciplinaList.at(0).getProfesor() == "vancea");


	// testam cu ora inexistenta
	try
	{
		disciplinaList = service.filterByOre(50);
	}
	catch (const Error& error)
	{
		assert(error.getMessage() == "Nu exista discipline de acest tip in baza de date! \n");
	}

	// teste pentru filtrarea dupa tip
	// testam cu un tip de masini existent in lista
	disciplinaList = service.filterByProfesor("ISTVAN");
	assert(disciplinaList.size() == 1);
	assert(disciplinaList.at(0).getDenumire() == "OOP");
	assert(disciplinaList.at(0).getOre() == 30);
	assert(disciplinaList.at(0).getTip() == "FRECVENTA");
	assert(disciplinaList.at(0).getProfesor() == "ISTVAN");

	// testam cu un PROFESOR  inexistent in lista
	try
	{
		disciplinaList = service.filterByProfesor("ASDF");
	}
	catch (const Error& error)
	{
		assert(error.getMessage() == "Nu exista discipline de acest tip in baza de date! \n");
	}

	// sortam descrescator dupa DENUMIRE
	disciplinaList = service.sortByDenumire('d');
	assert(disciplinaList.at(0).getDenumire() == "csa");

	// sortam crescator dupa denumire
	disciplinaList = service.sortByDenumire('c');
	assert(disciplinaList.at(0).getDenumire() == "AG");

	// incercam sa sortam folosind un mod incorect
	try
	{
		disciplinaList = service.sortByDenumire('g');
	}
	catch (const Error& error)
	{
		assert(error.getMessage() == "Mod de sortare invalid!\n");
	}

	// sortam descrescator dupa ore
	disciplinaList = service.sortByOre('d');
	assert(disciplinaList.at(0).getOre() == 35);

	// sortam crescator dupa ore
	disciplinaList = service.sortByOre('c');
	assert(disciplinaList.at(0).getOre() == 30);

	// incercam sa sortam folosind un mod incorect
	try
	{
		disciplinaList = service.sortByOre('g');
	}
	catch (const Error& error)
	{
		assert(error.getMessage() == "Mod de sortare invalid!\n");
	}
	service.addDisciplina("FP", 30, "FRECVENTA", "ISTVAN");
	// sortam descrescator dupa profesor + tip
	disciplinaList = service.sortByProfesorTip('d');
	assert(disciplinaList.at(0).getProfesor() == "vancea");

	// sortam crescator dupa producator + model
	disciplinaList = service.sortByProfesorTip('c');
	assert(disciplinaList.at(0).getProfesor() == "BOIAN");

	// incercam sa sortam folosind un mod incorect
	try
	{
		disciplinaList = service.sortByProfesorTip('g');
	}
	catch (const Error& error)
	{
		assert(error.getMessage() == "Mod de sortare invalid!\n");
	}
	map<string, int>mp = service.report();
	assert(mp["FRECVENTA"] == 4);
	// testam functionalitatile clasei contractService
	ContractService contractService{ service };
	assert(contractService.contractSize() == 0);

	// adaugam o Disciplina existenta
	contractService.addDisciplina("FP");
	assert(contractService.contractSize() == 1);
	assert(contractService.contractList().at(0).getDenumire() == "FP");
	assert(contractService.contractList().at(0).getOre() == 30);
	assert(contractService.contractList().at(0).getTip() == "FRECVENTA");
	assert(contractService.contractList().at(0).getProfesor() == "ISTVAN");

	// incercam sa adaugam o disciplina inexistenta
	try
	{
		contractService.addDisciplina("ISTORIE FILOZOFICA");
	}
	catch (const Error& error)
	{
		assert(error.getMessage() == "Disciplina nu exista in baza de date!\n");
	}

	// incercam sa adaugam o disciplina cu o denumire invalida
	try
	{
		contractService.addDisciplina("111");
	}
	catch (const Error& error)
	{
		assert(error.getMessage() == "Denumirea disciplinei este invalida!\n");
	}

	// stergem toate disciplinele din lista de contract
	contractService.emptyContract();
	assert(contractService.contractSize() == 0);

	// generam discipline in contract
	contractService.populateContract(2);
	assert(contractService.contractSize() == 2);

	// incercam sa generam prea multe discipline in contract
	try
	{
		contractService.populateContract(10);
	}
	catch (const Error& error)
	{
		assert(error.getMessage() == "Numarul de discipline de generat este prea mare!\n");
	}
}