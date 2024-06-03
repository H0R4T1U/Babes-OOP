//
// Created by horatiu on 5/8/24.
//

#ifndef DISCIPLINAGUI_H
#define DISCIPLINAGUI_H

#include <vector>
#include <string>
#include <QtWidgets/QApplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QFormLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QRadioButton>
#include "../Service/DisciplinaService.h"
#include "../Domain/Observer.h"
#include <map>
#include "../Domain/disciplinaListModel.h"
#include <QSpinBox>
#include "cosCRUDGui.h"
#include "contracteRdonlyGui.h"
using namespace std;
class ContracteRDONLYGUI;

class disciplinaGui : public QWidget{


friend class CosCRUDGui;
friend class ContracteRDONLYGUI;

private:

    DisciplinaService& service;

    CosCRUDGui* contracte;
    ContracteRDONLYGUI* contracteRDOnly;

    // comutare
    QPushButton* butonLista{}, *butonRDOnly{};
    void initGui();
    void connectSignalSlots();
    char sortMode = 'c';

    //AFISARE
    QTableView* table;
    DisciplinaListModel* model;

    QHBoxLayout* lyRaportForm{};
    //FIELDS
    QLabel* denLbl = new QLabel("Denumirea Disciplinei:",nullptr);
    QLabel* denLbl2 = new QLabel("Denumirea Disciplinei:",nullptr);

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
    // SORT
    QPushButton* sortDenumireButton{},*sortOreButton{},*sortProfesorButton{};
    QLabel* descLabel = new QLabel("Descrescator");
    QCheckBox* checkDesc = new QCheckBox;
    QLabel* sort = new QLabel("Sorteaza:");

    // Contract
    QPushButton* addContract{}, * emptyContract{}, * populateContract{};
    QLineEdit* add{}, *populate{};

    void addGUI();
    void deleteGUI();
    void modifyGUI();
    void reloadListData(const std::vector<Disciplina>& list);
    void sortByDenumireGUI();
    void sortByOreGUI();
    void sortByProfesorGui();
    void filterByOreGUI();
    void filterByProfesorGUI();
    void modifySortState();
    void undoGUI();
    void raportGUI();
    void initialRaport();

public:

    explicit disciplinaGui(DisciplinaService& dS);
};



#endif //DISCIPLINAGUI_H
