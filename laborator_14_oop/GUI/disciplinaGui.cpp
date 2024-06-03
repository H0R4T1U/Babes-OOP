//
// Created by horatiu on 5/8/24.
//


#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QHeaderView>
#include <QStringList>
#include <qformlayout.h>
#include <QtWidgets/QWidget>
#include <QCheckBox>
#include <QStandardItemModel>
#include <qwindow.h>
#include "disciplinaGui.h"
#include "../Domain/Disciplina.h"
#include "../Domain/exception.h"
#include <map>
#include "cosCRUDGui.h"

void disciplinaGui::initGui() {
    auto* lyMain = new QHBoxLayout{};
    this->setLayout(lyMain);

    auto* left = new QWidget;
    auto* lyLeft = new QVBoxLayout{};
    left->setLayout(lyLeft);
    // schimba pe lista de contracte
    auto* form0 = new QWidget;
    auto* lyform0 = new QFormLayout;
    form0->setLayout(lyform0);
    butonLista = new QPushButton("Schimba pe cos CRUD");
    butonRDOnly = new QPushButton("Schimba pe cos ReadOnly");
    lyform0->addWidget(butonLista);
    lyform0->addWidget(butonRDOnly);
    lyLeft->addWidget(form0);
    // FIELDS
    auto* fieldForm = new QWidget;
    auto* lyFieldForm = new QFormLayout{};
    fieldForm->setLayout(lyFieldForm);
    denEdt = new QLineEdit;
    oreEdt = new QSpinBox;
    tipEdt = new QLineEdit;
    profesorEdt = new QLineEdit;

    lyFieldForm->addRow(denLbl,denEdt);
    lyFieldForm->addRow(oreLbl,oreEdt);
    lyFieldForm->addRow(tipLbl,tipEdt);
    lyFieldForm->addRow(profesorLbl,profesorEdt);
    lyLeft->addWidget(fieldForm);
    // CRUD
    auto* crudForm = new QWidget;
    auto* lyCrudForm = new QHBoxLayout{};
    crudForm->setLayout(lyCrudForm);
    lyCrudForm->addWidget(addButton);
    lyCrudForm->addWidget(deleteButton);
    lyCrudForm->addWidget(modifyButton);
    lyLeft->addWidget(crudForm);

    //SORTARE
    auto* sortForm = new QWidget;
    auto* lySortForm = new QHBoxLayout{};
    sortForm->setLayout(lySortForm);
    // Check box
    auto* checkDescWidget = new QWidget;
    auto* lyCheck = new QHBoxLayout{};
    checkDescWidget->setLayout(lyCheck);
    lyCheck->addWidget(descLabel);
    lyCheck->addWidget(checkDesc);

    // sort type
    auto* typeSort = new QWidget;
    auto* lyTypeSort = new QVBoxLayout{};
    typeSort->setLayout(lyTypeSort);
    sortDenumireButton = new QPushButton("Sorteaza dupa Denumire");
    sortOreButton = new QPushButton("Sorteaza dupa Ore");
    sortProfesorButton = new QPushButton("Sorteaza dupa Profesor");
    lyTypeSort->addWidget(sortDenumireButton);
    lyTypeSort->addWidget(sortOreButton);
    lyTypeSort->addWidget(sortProfesorButton);


    lySortForm->addWidget(checkDescWidget);
    lySortForm->addWidget(typeSort);
    lyLeft->addWidget(sortForm);
    //Filtrare ORE
    auto* filterForms = new QWidget;
    auto* lyFilterForm = new QHBoxLayout{};
    filterForms->setLayout(lyFilterForm);
    lyFilterForm->addWidget(filterOreButton);
    lyFilterForm->addWidget(filterProfesorButton);
    lyLeft->addWidget(filterForms);


    // Tabel Discipline
    auto* right = new QWidget;
    auto* lyright = new QVBoxLayout;
    right->setLayout(lyright);
    table = new QTableView();
    model = new DisciplinaListModel(table);
    table->setModel(model);

    lyright->addWidget(table);
    // UNDO
    lyright->addWidget(undoButton);

    // REPORT BUTTONS
    auto* raportForm = new QWidget;
    lyRaportForm = new QHBoxLayout{};
    raportForm->setLayout(lyRaportForm);
    map report = service.report();

    lyRaportForm->addWidget(raportButton);
    lyright->addWidget(raportForm);



    auto* wid = new QWidget;
    auto* lyWid = new QVBoxLayout;
    wid->setLayout(lyWid);
    auto* widForm = new QWidget;
    auto* lyWidForm = new QFormLayout;
    widForm->setLayout(lyWidForm);
    populateContract = new QPushButton("Populeaza lista de masini de spalat");
    populate = new QLineEdit();
    addContract = new QPushButton("Adauga masini in lista de spalat");
    add = new QLineEdit();
    emptyContract = new QPushButton("Goleste lista de masini de spalat");
    lyWid->addWidget(populate);
    lyWid->addWidget(populateContract);
    lyWidForm->addRow(denLbl2,add);
    lyWid->addWidget(widForm);
    lyWid->addWidget(addContract);
    lyWid->addWidget(emptyContract);

    // Final Linking;
    lyMain->addWidget(left);
    lyMain->addWidget(right);
    lyMain->addWidget(wid);

}




void disciplinaGui::addGUI() {
    try {
        const string den = denEdt->text().toStdString();
        denEdt->clear();
        const int ore = oreEdt->text().toInt();
        oreEdt->clear();
        const string tip = tipEdt->text().toStdString();
        tipEdt->clear();
        const string prof = profesorEdt->text().toStdString();
        profesorEdt->clear();

        service.addDisciplina(den,ore,tip,prof);
        reloadListData(service.getDisciplineList());
        QMessageBox::information(this, "Info", QString::fromStdString("Disciplina a fost adaugata cu succes!"));

    }catch (const ExistentDisciplinaError& err){
        QMessageBox::warning(this,"Eroare",QString::fromStdString(err.getMessage()));
    }catch (const InvalidDisciplinaError& err) {
        QMessageBox::warning(this,"Eroare",QString::fromStdString(err.getMessage()));
    }
}

void disciplinaGui::deleteGUI() {
    try {
        const string denumire = denEdt->text().toStdString();
        denEdt->clear();
        service.deleteDisciplina(denumire);
        reloadListData(service.getDisciplineList());
        QMessageBox::information(this,"Info","Disciplina stearsa cu succes!");
    }catch (InexistentDisciplinaError& err) {
        QMessageBox::warning(this,"Eroare",QString::fromStdString(err.getMessage()));
    }

}

void disciplinaGui::modifyGUI() {
    try {
        const string denumire = denEdt->text().toStdString();
        denEdt->clear();
        const int ore = oreEdt->text().toInt();
        oreEdt->clear();
        const string tip = tipEdt->text().toStdString();
        tipEdt->clear();
        const string profesor = profesorEdt->text().toStdString();
        profesorEdt->clear();
        service.modifyDisciplina(denumire,denumire,ore,tip,profesor);
        reloadListData(service.getDisciplineList());
        QMessageBox::information(this,"INFO",QString::fromStdString("Disciplina Modificata cu succes!"));
    } catch( InexistentDisciplinaError& err) {
        QMessageBox::warning(this,"Error",QString::fromStdString(err.getMessage()));
    } catch ( InvalidDisciplinaError& err) {
        QMessageBox::warning(this,"Error",QString::fromStdString(err.getMessage()));
    }
}



void disciplinaGui::reloadListData(const std::vector<Disciplina>& list) {
    model->setList(list);
}

void disciplinaGui::sortByDenumireGUI() {
    reloadListData(service.sortByDenumire(sortMode));
}
void disciplinaGui::sortByOreGUI() {
    reloadListData(service.sortByOre(sortMode));

}

void disciplinaGui::sortByProfesorGui() {
    reloadListData(service.sortByProfesorTip(sortMode));

}

void disciplinaGui::modifySortState() {
    if(checkDesc->isChecked()) {
        sortMode = 'd';
    }else {
        sortMode = 'c';
    }
}

void disciplinaGui::filterByOreGUI() {
    try {
        const int ore = oreEdt->text().toInt();
        oreEdt->clear();
        reloadListData(service.filterByOre(ore));

    }catch(EmptyListError& err) {
        QMessageBox::warning(this,"Error",QString::fromStdString(err.getMessage()));
    }
}
void disciplinaGui::filterByProfesorGUI() {
    try {
        const string profesor = profesorEdt->text().toStdString();
        profesorEdt->clear();
        reloadListData(service.filterByProfesor(profesor));
    }catch(EmptyListError& err) {
        QMessageBox::warning(this,"Error",QString::fromStdString(err.getMessage()));
    }
}

void disciplinaGui::undoGUI() {
    try {
        service.undo();
        reloadListData(service.getDisciplineList());
        QMessageBox::information(this,"Info",QString::fromStdString("Undo Realizat cu Succes"));
    } catch(const Error& err) {
        QMessageBox::warning(this,"Error",QString::fromStdString(err.getMessage()));
    }
}

void disciplinaGui::raportGUI() {
    map raport = service.report();
    string s;
    for(const auto& i : raport) {
        s+=i.first;
        s+= " ";
        s+= std::to_string(i.second);
        s += "\n";
    }
    QMessageBox::information(this,"Info",QString::fromStdString(s));
}
void disciplinaGui::initialRaport() {
    map raport = service.report();
    for(const auto& i : raport) {
        string tip = i.first;
        QPushButton* tipButton = new QPushButton(i.first.data());
        QObject::connect(tipButton,&QPushButton::clicked,this,[=]() {
            map x = service.report();
            string str = tipButton->text().toStdString();
            str.erase( remove(str.begin(), str.end(), '&'), str.end() );
            QMessageBox::information(this,"INFO",QString::number(x[str]));

        });
        lyRaportForm->addWidget(tipButton);


    }
}

disciplinaGui::disciplinaGui(DisciplinaService& dS): service{dS} {
        contracte = new CosCRUDGui(service);
        contracte->initContractGUI();
        contracte->reloadContractList(service.getContractList());
        contracte->connectSignalSlots();

        contracteRDOnly = new ContracteRDONLYGUI(contracte);
        contracteRDOnly->build_UI();

        initGui();
        connectSignalSlots();
        initialRaport();
        reloadListData(service.getDisciplineList());

    }

void disciplinaGui::connectSignalSlots() {
    service.addObserver(contracte);
    QObject::connect(addButton,&QPushButton::clicked,this,&disciplinaGui::addGUI);
    QObject::connect(deleteButton,&QPushButton::clicked,this,&disciplinaGui::deleteGUI);
    QObject::connect(modifyButton,&QPushButton::clicked,this,&disciplinaGui::modifyGUI);
    QObject::connect(checkDesc,&QCheckBox::stateChanged,this,&disciplinaGui::modifySortState);
    QObject::connect(sortDenumireButton,&QPushButton::clicked,this,&disciplinaGui::sortByDenumireGUI);
    QObject::connect(sortOreButton,&QPushButton::clicked,this,&disciplinaGui::sortByOreGUI);
    QObject::connect(sortProfesorButton,&QPushButton::clicked,this,&disciplinaGui::sortByProfesorGui);
    QObject::connect(filterOreButton,&QPushButton::clicked,this,&disciplinaGui::filterByOreGUI);
    QObject::connect(filterProfesorButton,&QPushButton::clicked,this,&disciplinaGui::filterByProfesorGUI);
    QObject::connect(undoButton,&QPushButton::clicked,this,&disciplinaGui::undoGUI);
    QObject::connect(raportButton,&QPushButton::clicked,this,&disciplinaGui::raportGUI);
    QObject::connect(butonLista, &QPushButton::clicked, [&]()
    {

        auto*  new_contracts = new CosCRUDGui(service);
        new_contracts->initContractGUI();
        new_contracts->connectSignalSlots();
        new_contracts->reloadContractList(service.getContractList());
        new_contracts->show();
        contracte->service.addObserver(new_contracts);

    });

    QObject::connect(butonRDOnly, &QPushButton::clicked, [&]()
    {
        auto* new_rdonly = new ContracteRDONLYGUI{contracte};
        new_rdonly->show();

    });

    QObject::connect(addContract, &QPushButton::clicked, [&]()
    {
        string den = add->text().toStdString();
        add->clear();
        service.addDisciplinaContract(den);
        contracte->service.notify();
    });

    QObject::connect(populateContract, &QPushButton::clicked, [&]()
    {
        int nr = populate->text().toInt();
        populate->clear();
        try
        {
            service.populateContract(nr);
            contracte->service.notify();
        }
        catch (...)
        {
            QMessageBox::warning(this, "Warning", "Numarul dat este prea mare");
        }
        contracte->service.notify();
    });

    QObject::connect(emptyContract, &QPushButton::clicked, [&]()
    {
        service.emptyContract();
        contracte->service.notify();
    });
}


/*
void disciplinaGui::exportToCsvGUI() {
    try {
        const string filename = contractFileNameEdit->text().toStdString();
        contractFileNameEdit->clear();
        service.exportCSV(filename);
    }catch(InvalidFileError& err) {
        QMessageBox::warning(this,"Error",QString::fromStdString(err.getMessage()));
    }

}
void disciplinaGui::exportToHtmlGUI() {
    try {
        const string filename = contractFileNameEdit->text().toStdString();
        contractFileNameEdit->clear();
        service.exportHTML(filename);
    }catch(InvalidFileError& err) {
        QMessageBox::warning(this,"Error",QString::fromStdString(err.getMessage()));
    }

}*/