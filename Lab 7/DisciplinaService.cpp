//
// Created by h on 3/28/24.
//

#include "DisciplinaService.h"
#include "disciplinaValidator.h"
#include <cassert>

using namespace std;

void DisciplinaService::addDisciplina(const string& denumire, int ore, const string& tip, const string& profesor) {
    if (rep.find(denumire) != -1)
        throw 1;
    if (validateDisciplina(denumire, ore, tip, profesor) == 0)
        throw 2;
    Disciplina d{ denumire,ore,tip,profesor };
    rep.store(d);
}

void DisciplinaService::deleteDisciplina(const string& denumire) {
	const int position = rep.find(denumire);
	if (position == -1)
		throw - 1; // masina nu exista in repo, deci nu avem ce sterge
	rep.remove(position);

}

void DisciplinaService::modifyDisciplina(const string& denumire, const string& new_Denumire, int ore, const string& tip, const string& profesor) {
    int position = rep.find(denumire);
    if (position == -1)
        throw 1;
    if (validateDisciplina(new_Denumire, ore, tip, profesor) == 0)
        throw 2;
    Disciplina d{ new_Denumire,ore,tip,profesor };
    rep.modify(position, d);

}

Disciplina DisciplinaService::findDisciplina(const string& denumire) const {
    const int position = rep.find(denumire);
    if (position == -1) {
        throw - 1;
    }
    return getDisciplineList().get(position);
}

const VectorDinamic<Disciplina>& DisciplinaService::getDisciplineList() const {
    return rep.getAll();
}
size_t DisciplinaService::listSize() const {
    return rep.size();
}

VectorDinamic<Disciplina> DisciplinaService::filterByOre(int ore) const
{
    VectorDinamic<Disciplina> disciplinaList = getDisciplineList();
    VectorDinamic<Disciplina> filteredList;
    int added = 0;
    for (int i = 0; i < disciplinaList.size(); i++)
        if (disciplinaList.get(i).getOre() == ore)
        {
            filteredList.add(disciplinaList.get(i));
            added = 1;
        }
    if (added == 0)
        throw 0;
    return filteredList;
}

VectorDinamic<Disciplina> DisciplinaService::filterByProfesor(const string& profesor) const
{
    VectorDinamic<Disciplina> disciplinaList = getDisciplineList();
    VectorDinamic<Disciplina> filteredList;
    int added = 0;
    for (int i = 0; i < disciplinaList.size(); i++)
        if (disciplinaList.get(i).getProfesor() == profesor)
        {
            filteredList.add(disciplinaList.get(i));
            added = 1;
        }
    if (added == 0)
        throw 0;
    return filteredList;
}

VectorDinamic<Disciplina> DisciplinaService::sortByDenumire(const char& mode) const
{
    VectorDinamic<Disciplina> sortedList = getDisciplineList();
    if (mode != 'c' && mode != 'd')
        throw 1;
    sortedList.sort(mode, 'd');
    return sortedList;
}

VectorDinamic<Disciplina> DisciplinaService::sortByOre(const char& mode) const
{
    VectorDinamic<Disciplina> sortedList = getDisciplineList();
    if (mode != 'c' && mode != 'd')
        throw 1;
    sortedList.sort(mode, 'o');
    return sortedList;
}

VectorDinamic<Disciplina> DisciplinaService::sortByProfesorTip(const char& mode) const
{
    VectorDinamic<Disciplina> sortedList = getDisciplineList();
    if (mode != 'c' && mode != 'd')
        throw 1;
    sortedList.sort(mode, 'p');
    return sortedList;
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
	catch (...)
	{
		assert(true);
	}

	// incercam sa adaugam o disciplina deja existenta
	try
	{
		service.addDisciplina("ASC", 30, "CLIO", "ALTELE");
	}
	catch (const int errCode)
	{
		assert(errCode == 1);
	}

	// verificam ca s-au adaugat masinile valide
	assert(service.getDisciplineList().get(0).getDenumire() == "ASC");
	assert(service.getDisciplineList().get(0).getOre() == 30);
	assert(service.getDisciplineList().get(0).getTip() == "FRECVENTA");
	assert(service.getDisciplineList().get(0).getProfesor() == "VANCEA");

	// verificam ca s-a modificat disciplina
	service.modifyDisciplina("ASC", "csa", 35, "Freq", "vancea");
	assert(service.getDisciplineList().get(0).getDenumire() == "csa");
	assert(service.getDisciplineList().get(0).getOre() == 35);
	assert(service.getDisciplineList().get(0).getTip() == "Freq");
	assert(service.getDisciplineList().get(0).getProfesor() == "vancea");

	// incercam sa modificam o disciplina inexistenta
	try
	{
		service.modifyDisciplina("asdf", "asdf", 55, "frecv", "xxx");
	}
	catch (...)
	{
		assert(true);
	}

	try
	{
		service.modifyDisciplina("FP", "asc1", -5, "TEST", "TEST");
	}
	catch (...)
	{
		assert(true);
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
	catch (...)
	{
		assert(true);
	}

	// stergem o disciplina si verificam ca s-a micsorat marimea
	service.deleteDisciplina("FP");
	assert(service.listSize() == 4);

	// incercam sa stergem o disciplina inexistenta
	try
	{
		service.deleteDisciplina("ASDF");
	}
	catch (...)
	{
		assert(true);
	}


	// teste pentru filtrarea dupa ore
	// testam cu ore existente
	VectorDinamic<Disciplina> disciplinaList = service.filterByOre(35);
	assert(disciplinaList.size() == 1);
	assert(disciplinaList.get(0).getDenumire() == "csa");
	assert(disciplinaList.get(0).getOre() == 35);
	assert(disciplinaList.get(0).getTip() == "Freq");
	assert(disciplinaList.get(0).getProfesor() == "vancea");


	// testam cu ora inexistenta
	try
	{
		disciplinaList = service.filterByOre(50);
	}
	catch (...)
	{
		assert(true);
	}

	// teste pentru filtrarea dupa tip
	// testam cu un tip de masini existent in lista
	disciplinaList = service.filterByProfesor("ISTVAN");
	assert(disciplinaList.size() == 1);
	assert(disciplinaList.get(0).getDenumire() == "OOP");
	assert(disciplinaList.get(0).getOre() == 30);
	assert(disciplinaList.get(0).getTip() == "FRECVENTA");
	assert(disciplinaList.get(0).getProfesor() == "ISTVAN");

	// testam cu un PROFESOR  inexistent in lista
	try
	{
		disciplinaList = service.filterByProfesor("ASDF");
	}
	catch (...)
	{
		assert(true);
	}

	// sortam descrescator dupa DENUMIRE
	disciplinaList = service.sortByDenumire('d');
	assert(disciplinaList.get(0).getDenumire() == "csa");

	// sortam crescator dupa denumire
	disciplinaList = service.sortByDenumire('c');
	assert(disciplinaList.get(0).getDenumire() == "AG");

	// incercam sa sortam folosind un mod incorect
	try
	{
		disciplinaList = service.sortByDenumire('g');
	}
	catch (...)
	{
		assert(true);
	}

	// sortam descrescator dupa ore
	disciplinaList = service.sortByOre('d');
	assert(disciplinaList.get(0).getOre() == 35);

	// sortam crescator dupa ore
	disciplinaList = service.sortByOre('c');
	assert(disciplinaList.get(0).getOre() == 30);

	// incercam sa sortam folosind un mod incorect
	try
	{
		disciplinaList = service.sortByOre('g');
	}
	catch (...)
	{
		assert(true);
	}
	service.addDisciplina("FP", 30, "FRECVENTA", "ISTVAN");
	// sortam descrescator dupa profesor + tip
	disciplinaList = service.sortByProfesorTip('d');
	assert(disciplinaList.get(0).getProfesor() == "vancea");

	// sortam crescator dupa producator + model
	disciplinaList = service.sortByProfesorTip('c');
	assert(disciplinaList.get(0).getProfesor() == "BOIAN");

	// incercam sa sortam folosind un mod incorect
	try
	{
		disciplinaList = service.sortByProfesorTip('g');
	}
	catch (...)
	{
		assert(true);
	}
}