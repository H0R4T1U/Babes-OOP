#pragma once
#include <iostream>
#include <cassert>	
#include "Disciplina.h"

template <typename Disciplina>
class Iterator;
template <typename Disciplina>
class VectorDinamic
{
public:
	// constructorul clasei
	VectorDinamic();

	// constructorul de copiere
	VectorDinamic(const VectorDinamic& vd);

	// destructorul clasei
	~VectorDinamic();

	// move constructor
	VectorDinamic& operator=(VectorDinamic&& vd) noexcept;

	// adaugarea unui element in vector
	void add(const Disciplina& c);

	// stergerea unui element din vector
	void remove(int poz);

	// getter pentru elementul de pe pozitia poz
	Disciplina& get(int poz) const noexcept;

	// setter pentru elementul de pe pozitia poz
	void set(int poz, const Disciplina& c);

	// getter pentru lungimea vectorului
	int size() const noexcept;

	// functie de sortare
	void sort(const char& mode, const char& field);

	// operator assignment
	VectorDinamic& operator=(const VectorDinamic& vd);

	friend class Iterator<Disciplina>;

	// returneaza un iterator la inceputul vectorului
	Iterator<Disciplina> begin();

	// returneaza un iterator la sfarsitul vectorului
	Iterator<Disciplina> end();

private:
	// dimensiunea curenta a vectorului
	int currentDIM;

	// dimensiunea maxima a vectorului
	int maximumDIM;

	// pointer la vectorul de masini
	Disciplina* DisciplinaList;

	// functie Disciplinae aloca spatiu daca este nevoie
	void ensureCapacity();
};

// constructor
template<typename Disciplina>
VectorDinamic<Disciplina>::VectorDinamic() : currentDIM{ 0 }, maximumDIM{ 1 }, DisciplinaList{ new Disciplina[1] } {};

// constructor de copiere
template<typename Disciplina>
VectorDinamic<Disciplina>::VectorDinamic(const VectorDinamic<Disciplina>& vd)
{
	DisciplinaList = new Disciplina[vd.maximumDIM];
	for (int i = 0; i < vd.currentDIM; i++)
		if (i < vd.maximumDIM)
			DisciplinaList[i] = vd.DisciplinaList[i];
	currentDIM = vd.currentDIM;
	maximumDIM = vd.maximumDIM;
}

// destructor
template<typename Disciplina>
VectorDinamic<Disciplina>::~VectorDinamic()
{
	delete[] DisciplinaList;
}

// move constructor
// construim un nou vector dintr-un r-value (la return)
template<typename Disciplina>
VectorDinamic<Disciplina>& VectorDinamic<Disciplina>::operator=(VectorDinamic<Disciplina>&& vd) noexcept
{
	delete[] DisciplinaList;
	DisciplinaList = vd.DisciplinaList;
	currentDIM = vd.currentDIM;
	maximumDIM = vd.maximumDIM;
	vd.DisciplinaList = nullptr;
	vd.currentDIM = 0;
	vd.maximumDIM = 0;
	return *this;
}

// adaugarea unui element in vector
template<typename Disciplina>
void VectorDinamic<Disciplina>::add(const Disciplina& c)
{
	ensureCapacity();
	DisciplinaList[currentDIM++] = c;
}

// stergerea elementului de pe pozitia poz din vector
template<typename Disciplina>
void VectorDinamic<Disciplina>::remove(int poz)
{
	for (auto i = poz; i < currentDIM - 1; i++)
		DisciplinaList[i] = DisciplinaList[i + 1];
	currentDIM--;
}

// getter pentru un element de pe pozitia poz din vector
template<typename Disciplina>
Disciplina& VectorDinamic<Disciplina>::get(int poz) const noexcept
{
	return DisciplinaList[poz];
}

// setter pentru un element de pe pozitia poz din vector
template<typename Disciplina>
void VectorDinamic<Disciplina>::set(int poz, const Disciplina& c)
{
	DisciplinaList[poz] = c;
}

// getter pentru lungimea vectorului
template<typename Disciplina>
int VectorDinamic<Disciplina>::size() const noexcept
{
	return currentDIM;
}

// alocam spatiu in plus daca este cazul
template<typename Disciplina>
void VectorDinamic<Disciplina>::ensureCapacity()
{
	if (currentDIM < maximumDIM)
		return;

	maximumDIM = maximumDIM * 2;
	Disciplina* aux = new Disciplina[maximumDIM];
	for (int i = 0; i < currentDIM; i++)
		aux[i] = DisciplinaList[i];
	delete[] DisciplinaList;
	DisciplinaList = aux;
}

// move constructor
template<typename Pet>
VectorDinamic<Pet>& VectorDinamic<Pet>::operator=(const VectorDinamic<Pet>& vd)
{
	delete[] DisciplinaList;
	DisciplinaList = new Pet[vd.maximumDIM];
	for (int i = 0; i < vd.currentDIM; i++)
		DisciplinaList[i] = vd.DisciplinaList[i];
	currentDIM = vd.currentDIM;
	maximumDIM = vd.maximumDIM;
	return *this;
}

// functia de comparare pentru sortare
inline int cmpF(const char& mode, const char& field, const Disciplina& Disciplina1, const Disciplina& Disciplina2)
{
	if (field == 'd') // sortam dupa denumire
	{
		if (mode == 'c') // sortam crescator
			return Disciplina1.getDenumire() > Disciplina2.getDenumire();
		else
			return Disciplina1.getDenumire() < Disciplina2.getDenumire();
	}

	if (field == 'o') // sortam dupa ore
	{
		if (mode == 'c') // sortam crescator
			return Disciplina1.getOre() > Disciplina2.getOre();
		else
			return Disciplina1.getOre() < Disciplina2.getOre();
	}


	if (mode == 'c') // sortam crescator
		if (Disciplina1.getProfesor() == Disciplina2.getProfesor())
			return Disciplina1.getTip() > Disciplina2.getTip();
		else
			return Disciplina1.getProfesor() > Disciplina2.getProfesor();
	else
		if (Disciplina1.getProfesor() == Disciplina2.getProfesor())
			return Disciplina1.getTip() < Disciplina2.getTip();
		else
			return Disciplina1.getProfesor() < Disciplina2.getProfesor();

}

// sortarea vectorului de masini
template<typename Disciplina>
void VectorDinamic<Disciplina>::sort(const char& mode, const char& field)
{
	int b = 0;
	while (b == 0)
	{
		b = 1;
		for (int i = 0; i < currentDIM - 1; i++)
			if (cmpF(mode, field, DisciplinaList[i], DisciplinaList[i + 1]))
			{
				swap(DisciplinaList[i], DisciplinaList[i + 1]);
				b = 0;
			}
	}
}

template<typename Disciplina>
class Iterator {
private:
	const VectorDinamic<Disciplina>& v;
	int poz = 0;
public:
	// constructorul clasei Iterator
	Iterator(const VectorDinamic<Disciplina>& v) noexcept;

	// constructor 
	Iterator(const VectorDinamic<Disciplina>& v, int poz)noexcept;

	// verifiDisciplinaea iteratorului 
	bool valid()const;
	int getPoz()const;
	// getter pentru elementul curent
	Disciplina& element() const;

	// trecerea la urmatorul element
	void next();

	// overload operator*
	// returneaza elementul []
	Disciplina& operator*();

	// overload operator++
	Iterator& operator++();

	// overload operator ==
	bool operator==(const Iterator& ot)noexcept;

	// overload operator !=
	bool operator!=(const Iterator& ot)noexcept;
};

template<typename Disciplina>
Iterator<Disciplina>::Iterator(const VectorDinamic<Disciplina>& v) noexcept :v{ v } {}

template<typename Disciplina>
Iterator<Disciplina>::Iterator(const VectorDinamic<Disciplina>& v, int poz)noexcept : v{ v }, poz{ poz } {}

template<typename Disciplina>
bool Iterator<Disciplina>::valid()const {
	return poz < v.currentDIM;
}

template<typename Disciplina>
Disciplina& Iterator<Disciplina>::element() const {
	return v.DisciplinaList[poz];
}

template<typename Disciplina>
void Iterator<Disciplina>::next() {
	poz++;
}

template<typename Disciplina>
Disciplina& Iterator<Disciplina>::operator*() {
	return element();
}

template<typename Disciplina>
Iterator<Disciplina>& Iterator<Disciplina>::operator++() {
	next();
	return *this;
}

template<typename Disciplina>
bool Iterator<Disciplina>::operator==(const Iterator<Disciplina>& ot) noexcept {
	return poz == ot.poz;
}
template<typename Disciplina>
int Iterator<Disciplina>::getPoz()const {
	return poz;
}

template<typename Disciplina>
bool Iterator<Disciplina>::operator!=(const Iterator<Disciplina>& ot)noexcept {
	return !(*this == ot);
}

template<typename Disciplina>
Iterator<Disciplina> VectorDinamic<Disciplina>::begin()
{
	return Iterator<Disciplina>(*this);
}

template<typename Disciplina>
Iterator<Disciplina> VectorDinamic<Disciplina>::end()
{
	return Iterator<Disciplina>(*this, currentDIM);
}