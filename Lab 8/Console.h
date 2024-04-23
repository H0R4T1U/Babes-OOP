#pragma once
#include "Disciplina.h"
#include "DisciplinaService.h"

class DisciplinaConsole
{
private:
    DisciplinaService& service;
    ContractService& contractService;
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
    void generateReport();
public:
    explicit DisciplinaConsole(DisciplinaService& dS,ContractService& cS) : service{ dS }, contractService{ cS } {};
    DisciplinaConsole(const DisciplinaConsole& dS) = delete;
    void start();
};