//
// Created by horatiu on 5/8/24.
//

#ifndef DISCIPLINAGUI_H
#define DISCIPLINAGUI_H
#include <QLabel>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include "../Service/DisciplinaService.h"
#include <string>
#include <QTableWidget>
#include <QSpinBox>
class DisciplinaGui : public QWidget{
private:
    DisciplinaService& service;
    void initGui();
    void connectSignalSlots();
    char sortMode = 'c';
    //AFISARE
    QTableWidget* table = new QTableWidget;
    QTableWidget* contracteTable = new QTableWidget;

    //FIELDS
    QLabel* denLbl = new QLabel("Denumirea Disciplinei:",nullptr);
    QLabel* oreLbl = new QLabel("Nr ore al Disciplinei:",nullptr);
    QLabel* tipLbl = new QLabel("Tipul Disciplinei:",nullptr);
    QLabel* profesorLbl = new QLabel("Profesorul Disciplinei:",nullptr);
    QLineEdit* denEdt{},*tipEdt{},*profesorEdt{};
    QSpinBox* oreEdt{};
    //CRUD
    QPushButton* addButton = new QPushButton("Adauga Disciplina!");
    QPushButton* deleteButton = new QPushButton("Sterge Disciplina!");
    QPushButton* modifyButton = new QPushButton("Modifica Disciplina!");
    //FILTER
    QPushButton* filterOreButton = new QPushButton("Filtreaza Ora");
    QPushButton* filterProfesorButton = new QPushButton("Filtreaza Profesor");
    // UNDO
    QPushButton* undoButton = new QPushButton("UNDO");
    // RAPORT
    QPushButton* raportButton = new QPushButton("Genereaza raport");
    QPushButton* frecvButton{};
    QPushButton* faraFrecvButton{};
    // SORT
    QPushButton* sortDenumireButton{},*sortOreButton{},*sortProfesorButton{};
    QLabel* descLabel = new QLabel("Descrescator");
    QCheckBox* checkDesc = new QCheckBox;
    QLabel* sort = new QLabel("Sorteaza:");
    // Contract
    QPushButton* startContractGuiButton = new QPushButton{"Contract Menu"};
    QLabel* contractDenLabel = new QLabel("Denumire:");
    QLabel* contractNumberLabel = new QLabel("Nr discipline de adaugat:");
    QLabel* contractFileNameLabel = new QLabel("File Name:");
    QLineEdit* contractDenEdit{};
    QLineEdit* contractFileNameEdit{};
    QSpinBox* contractNrEdit{};
    QPushButton* addDisciplinaToContractButton = new QPushButton("Adauga la Contract");
    QPushButton* populateContractButton = new QPushButton("Populeaza Contract");
    QPushButton* emptyContractButton  = new QPushButton("Goleste Contract");
    QPushButton* toHtmlButton  = new QPushButton("Export HTML");
    QPushButton* toCsvButton  = new QPushButton("Export CSV");
    void addGUI();
    void deleteGUI();
    void modifyGUI();
    void reloadData(const std::vector<Disciplina> list);
    void reloadContractData(const std::vector<Disciplina> list);
    void sortByDenumireGUI();
    void sortByOreGUI();
    void sortByProfesorGui();
    void filterByOreGUI();
    void filterByProfesorGUI();
    void modifySortState();
    void undoGUI();
    void raportGUI();
    void contractInitGUI();
    void addDisciplinaToContractGUI();
    void clearContractGUI();
    void populateContractGUI();
    void exportToHtmlGUI();
    void exportToCsvGUI();
public:
    explicit DisciplinaGui(DisciplinaService& dS ) : service{dS} {
        initGui();
        connectSignalSlots();
        reloadData(service.getDisciplineList());
    }
};



#endif //DISCIPLINAGUI_H
