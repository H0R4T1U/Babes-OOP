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
    static void printAllDiscipline(const VectorDinamic<Disciplina>& carList);
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

public:
    explicit DisciplinaConsole(DisciplinaService& dS) : service{ dS } {};
    DisciplinaConsole(const DisciplinaConsole& dS) = delete;
    void start();
};