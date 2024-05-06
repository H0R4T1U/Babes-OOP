//
// Created by h on 3/28/24.
//

#include "DisciplinaService.h"
#include "disciplinaValidator.h"
#include <cassert>
#include <algorithm>
#include <random>
#include <chrono>
#include <fstream>
#include "exception.h"
#pragma warning( disable : 4244 )
using namespace std;

void DisciplinaService::addDisciplina(const string& denumire, int ore, const string& tip, const string& profesor) {
	if (rep.find(denumire) >= 0)
		throw ExistentDisciplinaError("Disciplina exista deja in baza de date!\n");
	if (validateDisciplina(denumire, ore, tip, profesor) == 0)
		throw InvalidDisciplinaError("Datele disciplinei sunt invalide\n");
	Disciplina d{ denumire,ore,tip,profesor };
	try {
		rep.store(d);
		undoActions.push_back(make_unique<UndoAdd>(rep, d));
	}
	catch (const float& prob)
	{
		cout << "Probabilitatea este: " << prob << endl;
		undoActions.push_back(make_unique<UndoAdd>(rep, d));
	}
	
}

void DisciplinaService::deleteDisciplina(const string& denumire) {
	const int position = rep.find(denumire);
	if (position < 0)
		throw InexistentDisciplinaError("disciplina nu exista in baza de date!\n");
	undoActions.push_back(make_unique<UndoRemove>(rep, rep.getAll().at(position)));
	try
	{
		rep.remove(position);
	}

	catch (const float& prob)
	{
		cout << "Probabilitatea este: " << prob << endl;
	}

}

void DisciplinaService::modifyDisciplina(const string& denumire, const string& new_Denumire, int ore, const string& tip, const string& profesor) {
	int position = rep.find(denumire);
	if (position < 0)
		throw InexistentDisciplinaError("disciplina nu exista in baza de date!\n");

	else if (validateDisciplina(new_Denumire, ore, tip, profesor) == 0)
		throw InvalidDisciplinaError("Datele disciplinei sunt invalide!\n");
	Disciplina d{ new_Denumire,ore,tip,profesor };
	undoActions.push_back(make_unique<UndoModify>(rep, rep.getAll().at(position), d));
	try
	{
		rep.modify(position, d);
	}

	catch (const float& prob)
	{
		cout << "Probabilitatea este: " << prob << endl;
	}

}
void DisciplinaService::undo()
{
	if (undoActions.empty())
		throw EmptyListError("Nu mai exista operatii la care sa executam undo!\n");
	try
	{
		undoActions.back()->doUndo();
	}
	catch (const float& prob)
	{
		cout << "Probabilitatea este: " << prob << endl;
		undoActions.pop_back();
	}
}
Disciplina DisciplinaService::findDisciplina(const string& denumire) const {
	const int position = rep.find(denumire);
	if (position < 0) {
		throw InexistentDisciplinaError("Disciplina nu exista in baza de date!\n");
	}
	return getDisciplineList().at(position);
}

const vector<Disciplina> DisciplinaService::getDisciplineList() const {
	return rep.getAll();
}
size_t DisciplinaService::listSize() const {
	return rep.size();
}

vector<Disciplina> DisciplinaService::filterByOre(int ore) const
{

	vector<Disciplina> filteredList;
	auto& all = rep.getAll();
	copy_if(all.begin(), all.end(), back_inserter(filteredList), [ore](const Disciplina& d) { return d.getOre() == ore; });

	if (filteredList.empty()) {
		throw EmptyListError("Nu exista discipline de acest tip in baza de date! \n");
	}
	return filteredList;
}

vector<Disciplina> DisciplinaService::filterByProfesor(const string& profesor) const
{
	vector<Disciplina> filteredList;
	auto& all = rep.getAll();
	copy_if(all.begin(), all.end(), back_inserter(filteredList), [profesor](const Disciplina& d) { return d.getProfesor() == profesor; });

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
void DisciplinaService::addDisciplinaContract(const string& denumire)
{
	if (validateDenumire(denumire) == 0)
		throw InvalidDenumire("Denumirea disciplinei este invalida!\n");
	try
	{
		Disciplina disciplina = findDisciplina(denumire);
		contractRepo.store(disciplina);
	}
	catch (const Error& error)
	{
		throw error;
	}
}

void DisciplinaService::emptyContract()
{
	while (contractRepo.size())
		contractRepo.remove(0);
}
void DisciplinaService::populateContract(size_t number)
{
	if (number > listSize())
		throw InvalidGenerateNumber("Numarul de discipline de generat este prea mare!\n");
	vector<Disciplina> copyDisciplinaList = getDisciplineList();
	auto seed = chrono::system_clock::now().time_since_epoch().count();
	shuffle(copyDisciplinaList.begin(), copyDisciplinaList.end(), default_random_engine(seed));
	for (size_t i = 0; i < number; i++)
		contractRepo.store(copyDisciplinaList.at(i));
}
void DisciplinaService::exportCSV(const string& fileName)
{
	ofstream out;
	out.open(fileName, ios::trunc);
	if (!out.is_open())
		throw InvalidFileError("Fisierul nu a putut fi deschis!\n");
	for (const auto& d : contractRepo.getAll())
		out << d.getDenumire() << ',' << d.getOre() << ',' << d.getTip() << ',' << d.getProfesor() << '\n';
	out.close();
}

void DisciplinaService::exportHTML(const string& fileName)
{
	ofstream out;
	out.open(fileName, ios::trunc);
	if (!out.is_open())
		throw InvalidFileError("Fisierul nu a putut fi deschis!\n");
	out << "<html><body>" << endl << "<table border=\"1\" style=\"width:100 % \">" << endl;
	for (const auto& d : contractRepo.getAll())
		out << "<tr>" << endl << "<td>" << d.getDenumire() << "</td>" << endl << "<td>" << d.getOre() << "</td>" << endl << "<td>" << d.getTip() << "</td>" << endl << "<td>" << d.getProfesor() << "</td>" << endl << "</tr>" << endl;
	out << "</table>" << endl << "</body></html>" << endl;
	out.close();
}
void testService()
{
	Repo repo;
	Repo contractRepo;
	DisciplinaService service{ repo,contractRepo };
	// incercam sa executam undo fara operatii
	try
	{
		service.undo();
	}
	catch (const Error& error)
	{
		assert(error.getMessage() == "Nu mai exista operatii la care sa executam undo!\n");
	}
	// adaugam cateva DISCIPLINE
	service.addDisciplina("ASC", 30, "FRECVENTA", "VANCEA");
	service.addDisciplina("OOP", 30, "FRECVENTA", "ISTVAN");
	service.addDisciplina("FP", 30, "FRECVENTA", "ISTVAN");
	service.addDisciplina("SO", 30, "FRECVENTA", "BOIAN");
	service.addDisciplina("AG", 30, "FRECVENTA", "SUCIU");
	service.undo();
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
	service.undo();
	service.modifyDisciplina("ASC", "csa", 35, "Freq", "vancea");

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

	service.undo();
	assert(service.listSize() == 5);
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
	assert(disciplinaList.size() == 2);
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
	assert(service.contractSize() == 0);

	// adaugam o Disciplina existenta
	service.addDisciplinaContract("FP");
	assert(service.contractSize() == 1);
	assert(service.contractList().at(0).getDenumire() == "FP");
	assert(service.contractList().at(0).getOre() == 30);
	assert(service.contractList().at(0).getTip() == "FRECVENTA");
	assert(service.contractList().at(0).getProfesor() == "ISTVAN");

	// incercam sa adaugam o disciplina inexistenta
	try
	{
		service.addDisciplinaContract("ISTORIE FILOZOFICA");
	}
	catch (const Error& error)
	{
		assert(error.getMessage() == "Disciplina nu exista in baza de date!\n");
	}

	// incercam sa adaugam o disciplina cu o denumire invalida
	try
	{
		service.addDisciplinaContract("111");
	}
	catch (const Error& error)
	{
		assert(error.getMessage() == "Denumirea disciplinei este invalida!\n");
	}

	// stergem toate disciplinele din lista de contract
	service.emptyContract();
	assert(service.contractSize() == 0);

	// generam discipline in contract
	service.populateContract(2);
	assert(service.contractSize() == 2);

	// incercam sa generam prea multe discipline in contract
	try
	{
		service.populateContract(10);
	}
	catch (const Error& error)
	{
		assert(error.getMessage() == "Numarul de discipline de generat este prea mare!\n");
	}
	// incercam sa exportam in fisier CSV
	try
	{
		service.exportCSV("/test.csv");
	}
	catch (const Error& error)
	{
		assert(error.getMessage() == "Fisierul nu a putut fi deschis!\n");
	}

	// incercam sa exportam in fisier HTML
	try
	{
		service.exportHTML("/test.html");
	}
	catch (const Error& error)
	{
		assert(error.getMessage() == "Fisierul nu a putut fi deschis!\n");
	}

	ofstream outCSV("test.csv", ios::trunc);
	ofstream outHTML("test.html", ios::trunc);
	service.emptyContract();

	// adaugam o masina in lista de spalat si o exportam in CSV
	service.addDisciplina("ASC", 30, "FRECVENTA", "VANCEA");
	service.addDisciplinaContract("ASC");
	service.exportCSV("test.csv");
	ifstream inCSV("test.csv");
	string testString;
	inCSV >> testString;
	assert(testString == "ASC,30,FRECVENTA,VANCEA");

	// adaugam o masina in lista de spalat si o exportam in HTML
	service.exportHTML("test.html");
	ifstream inHTML("test.html");
	inHTML >> testString;
	assert(testString == "<html><body>");
	// construim un maprepo si un mapservice
	MapRepo maprepo{ 0.2F };
	DisciplinaService mapservice{ maprepo, contractRepo };

	// adaugam o masina
	mapservice.addDisciplina("ASC", 30, "FRECV", "VANCEA");
	assert(mapservice.listSize() == 1);

	// executam undo
	mapservice.undo();
	assert(mapservice.listSize() == 0);

	// adaugam din nou masina
	mapservice.addDisciplina("ASC", 30, "FRECV", "VANCEA");
	assert(mapservice.listSize() == 1);

	// modificam si apoi stergem masina
	mapservice.modifyDisciplina("ASC", "FP", 45, "FRECV", "ISTVAN");
	mapservice.deleteDisciplina("FP");
	assert(mapservice.listSize() == 0);
}