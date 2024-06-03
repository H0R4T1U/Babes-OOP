#pragma once
#include <string>

// validarea unei masini
int validateDisciplina(std::string denumire, int ore, std::string tip, std::string profesor);
int validateDenumire(string denumire);

// teste pentru validator
void testValidate();