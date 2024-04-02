#pragma once
#include "../Domain/Disciplina.h"
#include "../Service/DisciplinaService.h"

class DisciplinaConsole
{
private:
    DisciplinaService& service;
    void addDisciplinaUI();
    void modifyDisciplinaUI();
    void removeDisciplinaUI();
    void findDisciplinaUI();
    static void printAllDiscipline(const vector<Disciplina>& carList);
    static void printMenu();

public:
    explicit DisciplinaConsole(DisciplinaService& dS) : service{dS} {};
    DisciplinaConsole(const DisciplinaConsole& dS) = delete;
    void start();
};