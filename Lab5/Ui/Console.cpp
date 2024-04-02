#include "Console.h"
#include "../Domain/Disciplina.h"
#include <iostream>
#include <string>

using namespace std;

void DisciplinaConsole::printAllDiscipline(const vector<Disciplina>& disciplinaList)
{
	cout << "Lista curenta de masini este:\n";
	for (int i = 0; i < disciplinaList.size(); i++)
		cout << i << ' ' << disciplinaList[i].getDenumire() << ' ' << disciplinaList[i].getOre() << ' ' << disciplinaList[i].getTip() << ' ' << disciplinaList[i].getProfesor() << '\n';
}

void DisciplinaConsole::printMenu()
{
	cout << "Selectati o optiune din meniul aplicatiei:\n";
	cout << "1. Adauga o Disciplina.\n";
	cout << "2. Modifica o Disciplina.\n";
	cout << "3. Sterge o Disciplina.\n";
	cout << "4. Cauta o Disciplina.\n";
	cout << "9. Iesire.\n";
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
	service.addDisciplina(denumire, ore, tip, profesor);
	cout << "Disciplina a fost adaugata cu succes!\n";
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
	service.modifyDisciplina(oldDenumire, newDenumire, ore, tip, profesor);
	cout << "Disciplina a fost modificata cu succes!\n";
}

void DisciplinaConsole::findDisciplinaUI()
{
	string denumire;
	Disciplina disciplinaToFind{"",0,"",""};
	cout << "Introduceti denumirea disciplnei pe careo cautati: ";
	cin >> denumire;
	disciplinaToFind = service.findDisciplina(denumire);
	cout << "Disciplina cautata este: \n";
	cout << disciplinaToFind.getDenumire() << ' ' << disciplinaToFind.getOre() << ' ' << disciplinaToFind.getTip() << ' ' << disciplinaToFind.getProfesor() << '\n';
}

void DisciplinaConsole::removeDisciplinaUI()
{
	string denumire;
	cout << "Introduceti numele disciplinei pe care doriti sa o stergeti: ";
	cin >> denumire;
	service.deleteDisciplina(denumire);
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
	populate(service);
	while (true)
	{
		printAllDiscipline(service.getDisciplineList());
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
		else break;

	}
}