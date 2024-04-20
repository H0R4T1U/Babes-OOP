#include "Disciplina.h"
#include <cassert>
#include <ctype.h>
int validateDisciplina(string denumire, int ore, string tip, string profesor)
{

	// validam denumirea
	// denumirea trebuie sa contina numai litere

	for (size_t i = 0; i < denumire.size(); i++)
		if (isdigit(denumire.at(i)))
			return 0;


	// validam tipul
	// trebuie sa contina doar litere

	for (size_t i = 0; i < tip.size(); i++)
		if (isdigit(tip.at(i)))
			return 0;

	// validam ora
	// trebuie sa fie cifra
	if (ore < 1) {
		return 0;
	}
	
	// validam profesorul
	//profesorul poate fi doar litere

	for (size_t i = 0; i < profesor.size(); i++)
		if (isdigit(profesor.at(i)))
			return 0;
	// daca a trecut de toate etapele de validare, datele masinii sunt bune

	return 1;
}

void testValidate()
{
	// testam functia de validare 
	// mai intai cu o disciplina valida
	// apoi cu cate o disciplina care sa contina cate un atribut invalid

	assert(validateDisciplina("ASC", 30, "Frecventa", "Vancea") == 1);
	assert(validateDisciplina("A1c", 30, "FR", "Vancea") == 0);
	assert(validateDisciplina("ASC", -1, "Frecventa", "Vancea") == 0);
	assert(validateDisciplina("ASC", 30, "Frecventa1", "Vancea") == 0);
	assert(validateDisciplina("ASC", 30, "Frecventa", "Vancea1") == 0);

}