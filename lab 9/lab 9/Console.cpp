#include "Console.h"
#include "Disciplina.h"
#include <iostream>
#include <string>
#include "exception.h"

using namespace std;

void DisciplinaConsole::printAllDiscipline(const vector<Disciplina>& disciplinaList)
{
	cout << "Lista curenta de masini este:\n";
	for (size_t i = 0; i < disciplinaList.size(); i++)
		cout << i << ' ' << disciplinaList.at(i).getDenumire() << ' ' << disciplinaList.at(i).getOre() << ' ' << disciplinaList.at(i).getTip() << ' ' << disciplinaList.at(i).getProfesor() << '\n';
}
void DisciplinaConsole::printContractMenu()
{
	cout << "Selectati o optiune din meniul urmator:\n";
	cout << "1. Goleste lista.\n";
	cout << "2. Adauga in lista.\n";
	cout << "3. Genereaza lista.\n";
	cout << "4. Exporta lista in fisier HTML.\n";
	cout << "5. Exporta lista in fisier CSV.\n";
	cout << "6. Revenire la meniul principal.\n";
}
void DisciplinaConsole::printMenu()
{
	cout << "Selectati o optiune din meniul aplicatiei:\n";
	cout << "1. Adauga o Disciplina.\n";
	cout << "2. Modifica o Disciplina.\n";
	cout << "3. Sterge o Disciplina.\n";
	cout << "4. Cauta o Disciplina.\n";
	cout << "5. Afiseaza Discipline.\n";
	cout << "6. Filtrare dupa Ore.\n";
	cout << "7. Filtrare dupa Profesor.\n";
	cout << "8. Sortare dupa Denumire.\n";
	cout << "9. Sortare dupa Ore.\n";
	cout << "10. Sortare dupa Profesor+Tip.\n";
	cout << "11. Meniul de creare contracte studiu.\n";
	cout << "12. Genereaza raport.\n";
	cout << "13. Undo.\n";
	cout << "14. Iesire.\n";
}

void DisciplinaConsole::addDisciplinaUI()
{
	string denumire, tip, profesor;
	int ore;
	cout << "Introduceti denumirea Disciplinei: ";
	cin >> denumire;
	cout << "Introduceti nr de ore al Disciplinei: ";
	cin >> ore;
	cout << "Introduceti tipul Disciplinei: ";
	cin >> tip;
	cout << "Introduceti Profesorul Disciplinei: ";
	cin >> profesor;
	try
	{
		service.addDisciplina(denumire, ore, tip, profesor);
		cout << "Disciplina a fost adaugata cu succes!\n";
	}
	catch (const Error& err)
	{
		cout << err.getMessage();
	}

}

void DisciplinaConsole::modifyDisciplinaUI()
{
	string oldDenumire, newDenumire, tip, profesor;
	int ore;
	cout << "Introduceti denumirea disciplinei pe care doriti sa o modificati: ";
	cin >> oldDenumire;
	cout << "Introduceti noua denumire a disciplinei:";
	cin >> newDenumire;
	cout << "Introduceti nr de ore al disciplinei: ";
	cin >> ore;
	cout << "Introduceti tipul disciplinei: ";
	cin >> tip;
	cout << "Introduceti profesorul disciplinei: ";
	cin >> profesor;
	try
	{
		service.modifyDisciplina(oldDenumire, newDenumire, ore, tip, profesor);
		cout << "Disciplina a fost modificata cu succes!\n";
	}
	catch (const Error& err)
	{
		cout << err.getMessage();
	}
}

void DisciplinaConsole::findDisciplinaUI()
{
	string denumire;
	cout << "Introduceti denumirea disciplnei pe careo cautati: ";
	cin >> denumire;


	try
	{
		Disciplina disciplinaToFind = service.findDisciplina(denumire);
		cout << "Disciplina cautata este: \n";
		cout << disciplinaToFind.getDenumire() << ' ' << disciplinaToFind.getOre() << ' ' << disciplinaToFind.getTip() << ' ' << disciplinaToFind.getProfesor() << '\n';
	}
	catch (const Error& err)
	{
		cout << err.getMessage();
	}
	;
	;
}

void DisciplinaConsole::removeDisciplinaUI()
{
	string denumire;
	cout << "Introduceti numele disciplinei pe care doriti sa o stergeti: ";
	cin >> denumire;

	try
	{
		service.deleteDisciplina(denumire);
		cout << "Disciplina a fost stearsa cu succes!\n";
	}
	catch (const Error& err)
	{
		cout << err.getMessage();
	}
}
void DisciplinaConsole::filtrareByOre()
{
	int ore;
	cout << "Introduceti nr de ore dupa care doriti sa filtrati: ";
	cin >> ore;
	try
	{
		vector<Disciplina> filteredList = service.filterByOre(ore);
		cout << "Lista de Discipline filtrate dupa ore este: \n";
		printAllDiscipline(filteredList);
	}
	catch (const Error& err)
	{
		cout << err.getMessage();
	}
}

void DisciplinaConsole::filterByProfesor()
{
	string profesor;
	cout << "Introduceti profesor-ul dupa care doriti sa filtrati: ";
	cin >> profesor;
	try
	{
		vector<Disciplina> filteredList = service.filterByProfesor(profesor);
		cout << "Lista de discipline filtrata dupa profesor este: \n";
		printAllDiscipline(filteredList);
	}
	catch (const Error& err)
	{
		cout << err.getMessage();
	}
}

void DisciplinaConsole::sortByDenumire()
{
	char mode;
	cout << "Introduceti d pentru sortare descrescatoare si c pentru sortare crescatoare: ";
	cin >> mode;
	try
	{
		vector<Disciplina> sortedList = service.sortByDenumire(mode);
		cout << "Lista sortata este: \n";
		printAllDiscipline(sortedList);
	}
	catch (const Error& err)
	{
		cout << err.getMessage();
	}
}

void DisciplinaConsole::sortByOre()
{
	char mode;
	cout << "Introduceti d pentru sortare descrescatoare si c pentru sortare crescatoare: ";
	cin >> mode;
	try
	{
		vector<Disciplina> sortedList = service.sortByOre(mode);
		cout << "Lista sortata este: \n";
		printAllDiscipline(sortedList);
	}
	catch (const Error& err)
	{
		cout << err.getMessage();
	}
}

void DisciplinaConsole::sortByProfesorTip()
{
	char mode;
	cout << "Introduceti d pentru sortare descrescatoare si c pentru sortare crescatoare: ";
	cin >> mode;
	try
	{
		vector<Disciplina> sortedList = service.sortByProfesorTip(mode);
		cout << "Lista sortata este: \n";
		printAllDiscipline(sortedList);
	}
	catch (const Error& err)
	{
		cout << err.getMessage();
	}
}

void populate(DisciplinaService& dS)
{
	dS.addDisciplina("ASC", 15, "frecventa", "Vancea");
	dS.addDisciplina("OOP", 20, "frecventa", "ISTVAN");
	dS.addDisciplina("POO", 30, "frecventa", "ISTVAN");
	dS.addDisciplina("AG", 5, "fara frecventa", "Suciu");
	dS.addDisciplina("Analiza", 100, "fara frecventa", "Berinde");
}
void DisciplinaConsole::emptyContractList()
{
	service.emptyContract();
	cout << "Lista a fost golita cu succes!\n";
}

void DisciplinaConsole::addToContractList()
{
	string disciplina;
	cout << "Introduceti numele discplinei pe care doriti sa o adaugati: ";
	cin >> disciplina;
	try
	{
		service.addDisciplinaContract(disciplina);
	}
	catch (const Error& err)
	{
		cout << err.getMessage();
	}
}

void DisciplinaConsole::generateContractList()
{
	size_t number;
	cout << "Introduceti numarul de discipline ce trebuie adaugate: ";
	cin >> number;
	try
	{
		service.populateContract(number);
	}
	catch (const Error& err)
	{
		cout << err.getMessage();
	}
}
void DisciplinaConsole::generateReport()
{
	map<string, int> rep = service.report();
	for (auto pr : rep)
		cout << pr.first << ' ' << pr.second << '\n';
}
void DisciplinaConsole::exportCSV()
{
	cout << "Introduceti numele fisierului in care doriti sa exportati: ";
	string fileName;
	cin >> fileName;
	try
	{
		service.exportCSV(fileName);
	}
	catch (const Error& err)
	{
		cout << err.getMessage();
	}
}

void DisciplinaConsole::exportHTML()
{
	cout << "Introduceti numele fisierului in care doriti sa exportati: ";
	string fileName;
	cin >> fileName;
	try
	{
		service.exportHTML(fileName);
	}
	catch (const Error& err)
	{
		cout << err.getMessage();
	}
}
void DisciplinaConsole::undo()
{
	try
	{
		service.undo();
	}
	catch (const Error& err)
	{
		cout << err.getMessage();
	}
}
void DisciplinaConsole::start()
{
	int option;
	populate(service);
	while (true)
	{

		printMenu();
		cin >> option;
		if (option == 1)
			addDisciplinaUI();
		else if (option == 2)
			modifyDisciplinaUI();
		else if (option == 3)
			removeDisciplinaUI();
		else if (option == 4)
			findDisciplinaUI();
		else if (option == 5)
			printAllDiscipline(service.getDisciplineList());
		else if (option == 6) {
			filtrareByOre();
		}
		else if (option == 7) {
			filterByProfesor();
		}
		else if (option == 8) {
			sortByDenumire();
		}
		else if (option == 9) {
			sortByOre();
		}
		else if (option == 10) {
			sortByProfesorTip();
		}
		else if (option == 11)
		{
			int contractOption = -1;
			while (1)
			{
				cout << "Sunt " << service.contractSize() << " discipline in contract\n";
				printAllDiscipline(service.contractList());
				printContractMenu();
				cin >> contractOption;
				if (contractOption == 1)
					emptyContractList();
				else if (contractOption == 2)
					addToContractList();
				else if (contractOption == 3)
					generateContractList();
				else if (contractOption == 4)
					exportHTML();
				else if (contractOption == 5)
					exportCSV();
				else break;
			}
		}
		else if (option == 12)
			generateReport();
		else if (option == 13)
			undo();
		else break;

	}
}