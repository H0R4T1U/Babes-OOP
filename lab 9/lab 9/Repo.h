//
// Created by h on 3/28/24.
//

#ifndef REPO_H
#define REPO_H

#include <string>
#include <vector>
#include "Disciplina.h"
#include <map>
using namespace std;
class AbstractRepo {
private:

public:
	AbstractRepo() = default;
    virtual void store(const Disciplina& d) = 0;
    virtual void modify(const __int64& position, const Disciplina& disciplina) = 0;
    virtual void remove(const __int64& position) = 0;
    virtual __int64 find(const string& denumire) const = 0 ;
    virtual const vector<Disciplina> getAll() const = 0;
    virtual size_t size() const = 0;
	virtual ~AbstractRepo() = default;
};
class MapRepo : public AbstractRepo
{
private:
	// dictionarul care retine masinile
	map<size_t, Disciplina> dict = {};

	// probabilitatea
	float prob;

public:
	// constructorul clasei MapRepo
	MapRepo(const float& prob) : prob{ prob } {};

	// adaugarea unei masini in dict
	void store(const Disciplina& d) override
	{
		dict.insert(pair<size_t, Disciplina>(dict.size(), d));
		throw prob;}

	// stergerea unei masini din dict
	void remove(const __int64& position) override
	{
		dict.erase(position);
		throw prob;}

	// modificarea unei masini din dict
	void modify(const __int64& position, const Disciplina& newD) override
	{
		dict.at(position) = newD;
		throw prob;}

	// cautarea unei masini in dict
	__int64 find(const string& denumire) const override
	{
		for (auto& pair : dict)
			if (pair.second.getDenumire() == denumire)
				return __int64(pair.first);
		return -1;
	}

	// lungimea dictionarului
	size_t size() const noexcept override
	{
		return dict.size();
	}

	// getter pentru lista de masini
	const vector<Disciplina> getAll() const override
	{
		vector<Disciplina> list = {};
		for (auto& pair : dict)
			list.push_back(pair.second);
		return list;
	}

	~MapRepo() override = default;
};
class Repo: public AbstractRepo {
	vector<Disciplina> all = {};
public:
    // constructor clasa
    Repo() = default;
    //nu permitem copierea de obiecte
    Repo(const Repo& ot) = delete;
    // adaugarea unei disciplini in vector
    void store(const Disciplina& d) override;
    // stergerea unei disciplini din vector
    void remove(const __int64&) override;
    // Modificarea unei disciplini din vector
    void modify(const __int64& position, const Disciplina& disciplina) override;
    // cautarea unei masini in vector
    __int64 find(const string& denumire) const override;
    // getter pentru lista curenta de discipline
    const vector<Disciplina> getAll() const  override;
    // getter pentru lungimea listei
    size_t size() const override;
};




void testRepo();
#endif //REPO_H
