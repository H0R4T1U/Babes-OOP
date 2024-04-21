	#pragma once
#include <string>
using namespace std;
class Error
{
private:
	// mesajul erorii
	string errorMessage;

public:
	// constructorul clasei de erori
	Error(string errorMessage) : errorMessage(errorMessage) {};

	// getter pentru mesajul erorii
	const string& getMessage() const noexcept
	{
		return errorMessage;
	}
};

class InvalidDisciplinaError : public Error
{
public:
	// constructorul clasei de erori de validare
	// eroarea apare atunci cand atributele unei discipline sunt invalide
	InvalidDisciplinaError(string errorMessage) : Error(errorMessage) {};
};

class InexistentDisciplinaError : public Error
{
public:
	// constructorul clasei de erori
	// eroarea apare atunci cand cautam / modificam / stergem o discipline inexistenta
	InexistentDisciplinaError(string errorMessage) : Error(errorMessage) {};
};

class ExistentDisciplinaError : public Error
{
public:
	// constructorul clasei de erori
	// eroarea apare atunci adaugam o Disciplina deja existenta
	ExistentDisciplinaError(string errorMessage) : Error(errorMessage) {};
};

class EmptyListError : public Error
{
public:
	// constructuroul clasei de erori
	// eroarea apare atunci cand lista de discipline este vida (la filtrari)
	EmptyListError(string errorMessage) : Error(errorMessage) {};
};

class InvalidSortingMode : public Error
{
public:
	// constructorul clasei de erori
	// eroarea apare atunci cand utilizatorul introduce un mod de sortare invalid
	InvalidSortingMode(string errorMessage) : Error(errorMessage) {};
};

class InvalidDenumire : public Error
{
public:
	// constructorul clasei de erori
	// eroarea apare atunci cand utilizatorul introduce o denumire invalida
	InvalidDenumire(string errorMessage) : Error(errorMessage) {};
};

class InvalidGenerateNumber : public Error
{
public:
	// constructorul clasei de erori
	// eroarea apare atunci cand utilizatorul vrea sa genereze mai multe discipline decat exista
	// in repository-ul curent
	InvalidGenerateNumber(string errorMessage) : Error(errorMessage) {};
};
class InvalidFileError : public Error
{
public:
	// constructorul clasei de erori
	// eroarea apare atunci cand nu putem deschide un fisier
	InvalidFileError(string errorMessage) : Error(errorMessage) {};
};