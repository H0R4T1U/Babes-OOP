#include "Console.h"
#include "Disciplina.h"
#include <iostream>
#include <string>

using namespace std;

void DisciplinaConsole::printAllDiscipline(const VectorDinamic<Disciplina>& disciplinaList)
{
	cout << "Lista curenta de masini este:\n";
	for (int i = 0; i < disciplinaList.size(); i++)
		cout << i << ' ' << disciplinaList.get(i).getDenumire() << ' ' << disciplinaList.get(i).getOre() << ' ' << disciplinaList.get(i).getTip() << ' ' << disciplinaList.get(i).getProfesor() << '\n';
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
	cout << "11. Iesire.\n";
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
	catch (const int errCode)
	{
		if (errCode == 1)
			cout << "Exista deja o disciplina cu acest nume!\n";
		else
			cout << "Datele disciplinei sunt invalide!\n";
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
		service.modifyDisciplina(oldDenumire,newDenumire, ore, tip, profesor);
		cout << "Disciplina a fost modificata cu succes!\n";
	}
	catch (const int errCode)
	{
		if (errCode == 1)
			cout << "Nu Exista disciplina cu acest nume!\n";
		else
			cout << "Datele disciplinei sunt invalide!\n";
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
	catch (...)
	{
		cout << "Disciplina nu exista in baza de date!\n";
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
	catch (...)
	{
		cout << "Disciplina cautata nu exista in baza de date!\n";
	}
}
void DisciplinaConsole::filtrareByOre()
{
	int ore;
	cout << "Introduceti nr de ore dupa care doriti sa filtrati: ";
	cin >> ore;
	try
	{
		VectorDinamic<Disciplina> filteredList = service.filterByOre(ore);
		cout << "Lista de Discipline filtrate dupa ore este: \n";
		printAllDiscipline(filteredList);
	}
	catch (...)
	{
		cout << "Nu exista discipline cu acest nr de ore!\n";
	}
}

void DisciplinaConsole::filterByProfesor()
{
	string profesor;
	cout << "Introduceti profesor-ul dupa care doriti sa filtrati: ";
	cin >> profesor;
	try
	{
		VectorDinamic<Disciplina> filteredList = service.filterByProfesor(profesor);
		cout << "Lista de discipline filtrata dupa profesor este: \n";
		printAllDiscipline(filteredList);
	}
	catch (...)
	{
		cout << "Nu exista discipline cu acest profesor!\n";
	}
}

void DisciplinaConsole::sortByDenumire()
{
	char mode;
	cout << "Introduceti d pentru sortare descrescatoare si c pentru sortare crescatoare: ";
	cin >> mode;
	try
	{
		VectorDinamic<Disciplina> sortedList = service.sortByDenumire(mode);
		cout << "Lista sortata este: \n";
		printAllDiscipline(sortedList);
	}
	catch (...)
	{
		cout << "Modul de sortare este invalid!\n";
	}
}

void DisciplinaConsole::sortByOre()
{
	char mode;
	cout << "Introduceti d pentru sortare descrescatoare si c pentru sortare crescatoare: ";
	cin >> mode;
	try
	{
		VectorDinamic<Disciplina> sortedList = service.sortByOre(mode);
		cout << "Lista sortata este: \n";
		printAllDiscipline(sortedList);
	}
	catch (...)
	{
		cout << "Modul de sortare este invalid!\n";
	}
}

void DisciplinaConsole::sortByProfesorTip()
{
	char mode;
	cout << "Introduceti d pentru sortare descrescatoare si c pentru sortare crescatoare: ";
	cin >> mode;
	try
	{
		VectorDinamic<Disciplina> sortedList = service.sortByProfesorTip(mode);
		cout << "Lista sortata este: \n";
		printAllDiscipline(sortedList);
	}
	catch (...)
	{
		cout << "Modul de sortare este invalid!\n";
	}
}

void populate(DisciplinaService& dS)
{
	dS.addDisciplina("ASC", 15, "frecventa", "Vancea");
	dS.addDisciplina("OOP", 20, "frecventa", "ISTVAN");
	dS.addDisciplina("POO", 30, "frecventa", "ISTVAN");
	dS.addDisciplina("AG", 5, "frecventa", "Suciu");
	dS.addDisciplina("Analiza", 100, "frecventa", "Berinde");
}

void DisciplinaConsole::start()
{
	int option;
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
		else break;

	}
}