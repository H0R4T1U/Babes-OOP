#pragma once
#include "Disciplina.h"
#include "DisciplinaService.h"

class DisciplinaConsole
{
private:
    DisciplinaService& service;

    void addDisciplinaUI();
    void modifyDisciplinaUI();
    void removeDisciplinaUI();
    void findDisciplinaUI();
    static void printAllDiscipline(const vector<Disciplina>& disciplinaList);
    static void printMenu();
    // filtrarea dupa Ore
    void filtrareByOre();

    // filtrarea dupa Profesor
    void filterByProfesor();

    // sortarea dupa denumire
    void sortByDenumire();

    // sortarea dupa ore
    void sortByOre();

    // sortarea dupa profesor + tip
    void sortByProfesorTip();
    // printarea meniului pentru crearea contractelor
    void printContractMenu();

    // golirea listei de discipline din contract
    void emptyContractList();

    // adauga in lista de discipline o disciplina
    void addToContractList();

    // genereaza aleatoriu lista de discipline 
    void generateContractList();
    // genereaza raport
    void generateReport();
    // exporteaza in csv file
    void exportCSV();
    // exporteaza in html file
    void exportHTML();
    // undo ultima operatie
    void undo();
public:
    explicit DisciplinaConsole(DisciplinaService& dS) : service{ dS } {};
    DisciplinaConsole(const DisciplinaConsole& dS) = delete;
    void start();
};