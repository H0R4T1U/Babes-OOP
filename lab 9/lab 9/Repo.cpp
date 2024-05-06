//
// Created by h on 3/28/24.
//

#include "Repo.h"

#include <cassert>


void Repo::store(const Disciplina& d) {
    all.push_back(d);
}


void Repo::remove(const __int64& position) {
    all.erase(all.begin() + position);
}

void Repo::modify(const __int64& position, const Disciplina& disciplina) {
    all.at(position) = disciplina;
}


__int64 Repo::find(const string& denumire)const {
    auto x = find_if(all.begin(), all.end(), [denumire](const Disciplina& d) {return d.getDenumire() == denumire; });
    const __int64 y = distance(all.begin(), x);
    if (y - all.size() == 0)
        return -1;
    return y;
}
size_t Repo::size() const
{
    return all.size();
}
const vector<Disciplina> Repo::getAll() const  {
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
    assert(repo.size() == 2);
    assert(repo.getAll().at(0).getDenumire() == testDisciplina1.getDenumire());
    assert(repo.getAll().at(0).getOre() == testDisciplina1.getOre());
    assert(repo.getAll().at(0).getTip() == testDisciplina1.getTip());
    assert(repo.getAll().at(0).getProfesor() == testDisciplina1.getProfesor());

    repo.modify(0, testDisciplina3);
    assert(repo.getAll().at(0).getDenumire() == testDisciplina3.getDenumire());
    assert(repo.getAll().at(0).getOre() == testDisciplina3.getOre());
    assert(repo.getAll().at(0).getTip() == testDisciplina3.getTip());
    assert(repo.getAll().at(0).getProfesor() == testDisciplina3.getProfesor());

    repo.remove(1);
    assert(repo.size() == 1);

    __int64 position = repo.find(testDisciplina3.getDenumire());
    assert(repo.getAll().at(position).getDenumire() == testDisciplina3.getDenumire());
    assert(repo.getAll().at(position).getOre() == testDisciplina3.getOre());
    assert(repo.getAll().at(position).getTip() == testDisciplina3.getTip());
    assert(repo.getAll().at(position).getProfesor() == testDisciplina3.getProfesor());

    position = repo.find("AG");

    assert(position == -1);
	// incercam sa adaugam o masina 
	MapRepo maprepo{ 0.2F };
	try
	{
		maprepo.store(testDisciplina1);
	}
	catch (const float& prob)
	{
		assert(prob == 0.2F);
	}

	try
	{
		maprepo.store(testDisciplina3);
	}
	catch (const float& prob)
	{
		assert(prob == 0.2F);
	}

	try
	{
		maprepo.modify(0, testDisciplina2);
	}
	catch (const float& prob)
	{
		assert(prob == 0.2F);
	}

	try
	{
		maprepo.remove(0);
	}
	catch (const float& prob)
	{
		assert(prob == 0.2F);
	}

	__int64 pos;
	pos = maprepo.find("Geografie");
	assert(pos == -1);
	pos = maprepo.find("OS");
	assert(pos == 1);
	assert(maprepo.size() == 1);
	assert(maprepo.getAll().at(0).getDenumire() == "OS");

}