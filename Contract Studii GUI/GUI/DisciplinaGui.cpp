//
// Created by horatiu on 5/8/24.
//

#include "DisciplinaGui.h"

#include "../Domain/exception.h"
#include "QtWidgets/QHBoxLayout"
#include "QtWidgets/QFormLayout"
#include "QtWidgets/QMessageBox"

void DisciplinaGui::initGui() {
    auto* lyMain = new QHBoxLayout{};
    this->setLayout(lyMain);

    auto* left = new QWidget;
    auto* lyLeft = new QVBoxLayout{};
    left->setLayout(lyLeft);

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

    // Lista Discipline
    auto* right = new QWidget;
    auto* lyright = new QVBoxLayout;
    right->setLayout(lyright);
    int m = 10;
    int n = 4;
    table = new QTableWidget(m,n);
    QStringList HeaderList;
    HeaderList << "Denumire"<<"Ore"<<"Tip"<<"Profesor";
    table->setHorizontalHeaderLabels(HeaderList);
    lyright->addWidget(table);
    // UNDO
    lyright->addWidget(undoButton);

    // REPORT BUTTONS
    auto* raportForm = new QWidget;
    auto* lyRaportForm = new QHBoxLayout{};
    raportForm->setLayout(lyRaportForm);
    map report = service.report();
    if(report["Frecventa"] > 0) {
        frecvButton = new QPushButton("Frecventa");
        lyRaportForm->addWidget(frecvButton);
    }
    if(report["Fara Frecventa"] > 0) {
        faraFrecvButton = new QPushButton("Fara Frecventa");
        lyRaportForm->addWidget(faraFrecvButton);
    }
    lyRaportForm->addWidget(raportButton);
    lyright->addWidget(raportForm);
    lyright->addWidget(startContractGuiButton);
    // Final Linking;
    lyMain->addWidget(left);
    lyMain->addWidget(right);

}
void DisciplinaGui::contractInitGUI() {
    auto* contractWindow = new QWidget;
    auto* lyContractWindow = new QHBoxLayout{};
    auto* contractLeftWindow = new QWidget;
    auto* lyContractLeftWindow = new QVBoxLayout{};
    contractLeftWindow->setLayout(lyContractLeftWindow);
    contractWindow->setLayout(lyContractWindow);
    contractWindow->setMinimumHeight(300);
    contractWindow->setMinimumWidth(400);
    // CRUD
    auto* crudContractForm = new QWidget;
    auto* lyCrudContractForm = new QFormLayout{};
    crudContractForm->setLayout(lyCrudContractForm);
    contractDenEdit = new QLineEdit{};
    contractNrEdit = new QSpinBox{};
    lyCrudContractForm->addRow(contractDenLabel,contractDenEdit);
    lyCrudContractForm->addRow(contractNumberLabel,contractNrEdit);
    lyContractLeftWindow->addWidget(crudContractForm);
    // CRUD BUTTONS
    auto* buttonContractForm = new QWidget;
    auto* lyButtonContactForm = new QHBoxLayout{};
    buttonContractForm->setLayout(lyButtonContactForm);
    lyButtonContactForm->addWidget(addDisciplinaToContractButton);
    lyButtonContactForm->addWidget(emptyContractButton);
    lyButtonContactForm->addWidget(populateContractButton);
    lyContractLeftWindow->addWidget(buttonContractForm);
    // EXPORTS FIELDS
    auto* exportContractForm = new QWidget;
    auto* lyExportContractForm = new QFormLayout{};
    exportContractForm->setLayout(lyExportContractForm);
    contractFileNameEdit = new QLineEdit{};
    lyExportContractForm->addRow(contractFileNameLabel,contractFileNameEdit);
    lyContractLeftWindow->addWidget(exportContractForm);
    // EXPORTS Buttons
    auto* exportButtonContractForm = new QWidget;
    auto* lyExportButtonContractForm = new QHBoxLayout;
    exportButtonContractForm->setLayout(lyExportButtonContractForm);
    lyExportButtonContractForm->addWidget(toHtmlButton);
    lyExportButtonContractForm->addWidget(toCsvButton);
    lyContractLeftWindow->addWidget(exportButtonContractForm);
    // Lista Discipline
    auto* contractRightWindow = new QWidget;
    auto* lyright = new QVBoxLayout;
    contractRightWindow->setLayout(lyright);
    int m = 10;
    int n = 4;
    contracteTable = new QTableWidget(m,n);
    QStringList HeaderList;
    HeaderList << "Denumire"<<"Ore"<<"Tip"<<"Profesor";
    table->setHorizontalHeaderLabels(HeaderList);
    lyright->addWidget(contracteTable);

    lyContractWindow->addWidget(contractLeftWindow);
    lyContractWindow->addWidget(contractRightWindow);

    // Final Linking
    contractWindow->show();
}
void DisciplinaGui::connectSignalSlots() {
    QObject::connect(addButton,&QPushButton::clicked,this,&DisciplinaGui::addGUI);
    QObject::connect(deleteButton,&QPushButton::clicked,this,&DisciplinaGui::deleteGUI);
    QObject::connect(modifyButton,&QPushButton::clicked,this,&DisciplinaGui::modifyGUI);
    QObject::connect(checkDesc,&QCheckBox::stateChanged,this,&DisciplinaGui::modifySortState);
    QObject::connect(sortDenumireButton,&QPushButton::clicked,this,&DisciplinaGui::sortByDenumireGUI);
    QObject::connect(sortOreButton,&QPushButton::clicked,this,&DisciplinaGui::sortByOreGUI);
    QObject::connect(sortProfesorButton,&QPushButton::clicked,this,&DisciplinaGui::sortByProfesorGui);
    QObject::connect(filterOreButton,&QPushButton::clicked,this,&DisciplinaGui::filterByOreGUI);
    QObject::connect(filterProfesorButton,&QPushButton::clicked,this,&DisciplinaGui::filterByProfesorGUI);
    QObject::connect(undoButton,&QPushButton::clicked,this,&DisciplinaGui::undoGUI);
    QObject::connect(raportButton,&QPushButton::clicked,this,&DisciplinaGui::raportGUI);
    QObject::connect(startContractGuiButton,&QPushButton::clicked,this,&DisciplinaGui::contractInitGUI);
    QObject::connect(addDisciplinaToContractButton,&QPushButton::clicked,this,&DisciplinaGui::addDisciplinaToContractGUI);
    QObject::connect(emptyContractButton,&QPushButton::clicked,this,&DisciplinaGui::clearContractGUI);
    QObject::connect(populateContractButton,&QPushButton::clicked,this,&DisciplinaGui::populateContractGUI);
    QObject::connect(toHtmlButton,&QPushButton::clicked,this,&DisciplinaGui::exportToHtmlGUI);
    QObject::connect(toCsvButton,&QPushButton::clicked,this,&DisciplinaGui::exportToCsvGUI);
    QObject::connect(frecvButton,&QPushButton::clicked,this,[&]() {
        map raport = service.report();
        QMessageBox::information(this,"INFO",QString::number(raport["Frecventa"]));
    });
    QObject::connect(faraFrecvButton,&QPushButton::clicked,this,[&]() {
        map raport = service.report();
        QMessageBox::information(this,"INFO",QString::number(raport["Fara Frecventa"]));
    });
}

void DisciplinaGui::addGUI() {
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
        reloadData(service.getDisciplineList());
        QMessageBox::information(this, "Info", QString::fromStdString("Disciplina a fost adaugata cu succes!"));

    }catch (const ExistentDisciplinaError& err){
        QMessageBox::warning(this,"Eroare",QString::fromStdString(err.getMessage()));
    }catch (const InvalidDisciplinaError& err) {
        QMessageBox::warning(this,"Eroare",QString::fromStdString(err.getMessage()));
    }
}
void DisciplinaGui::deleteGUI() {
    try {
        const string denumire = denEdt->text().toStdString();
        denEdt->clear();
        service.deleteDisciplina(denumire);
        reloadData(service.getDisciplineList());
        QMessageBox::information(this,"Info","Disciplina stearsa cu succes!");
    }catch (InexistentDisciplinaError& err) {
        QMessageBox::warning(this,"Eroare",QString::fromStdString(err.getMessage()));
    }

}

void DisciplinaGui::modifyGUI() {
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
        reloadData(service.getDisciplineList());
        QMessageBox::information(this,"INFO",QString::fromStdString("Disciplina Modificata cu succes!"));
    } catch( InexistentDisciplinaError& err) {
        QMessageBox::warning(this,"Error",QString::fromStdString(err.getMessage()));
    } catch ( InvalidDisciplinaError& err) {
        QMessageBox::warning(this,"Error",QString::fromStdString(err.getMessage()));
    }
}

void DisciplinaGui::reloadData(const std::vector<Disciplina> list) {
    table->clearContents();
    table->setRowCount(int(service.listSize()));

    int n = 0;
    for(auto& d : list) {
        table->setItem(n,0,new QTableWidgetItem(QString::fromStdString(d.getDenumire())));
        table->setItem(n,1,new QTableWidgetItem(QString::number(d.getOre())));
        table->setItem(n,2,new QTableWidgetItem(QString::fromStdString(d.getTip())));
        table->setItem(n,3,new QTableWidgetItem(QString::fromStdString(d.getProfesor())));
        n++;
    }
}
void DisciplinaGui::reloadContractData(const std::vector<Disciplina> list) {
    contracteTable->clearContents();
    contracteTable->setRowCount(int(service.listSize()));

    int n = 0;
    for(auto& d : list) {
        contracteTable->setItem(n,0,new QTableWidgetItem(QString::fromStdString(d.getDenumire())));
        contracteTable->setItem(n,1,new QTableWidgetItem(QString::number(d.getOre())));
        contracteTable->setItem(n,2,new QTableWidgetItem(QString::fromStdString(d.getTip())));
        contracteTable->setItem(n,3,new QTableWidgetItem(QString::fromStdString(d.getProfesor())));
        n++;
    }
}
void DisciplinaGui::sortByDenumireGUI() {
    reloadData(service.sortByDenumire(sortMode));
}
void DisciplinaGui::sortByOreGUI() {
    reloadData(service.sortByOre(sortMode));
}

void DisciplinaGui::sortByProfesorGui() {
    reloadData(service.sortByProfesorTip(sortMode));
}

void DisciplinaGui::modifySortState() {
    if(checkDesc->isChecked()) {
        sortMode = 'd';
    }else {
        sortMode = 'c';
    }
}

void DisciplinaGui::filterByOreGUI() {
    try {
        const int ore = oreEdt->text().toInt();
        oreEdt->clear();
        reloadData(service.filterByOre(ore));
    }catch(EmptyListError& err) {
        QMessageBox::warning(this,"Error",QString::fromStdString(err.getMessage()));
    }
}
void DisciplinaGui::filterByProfesorGUI() {
    try {
        const string profesor = profesorEdt->text().toStdString();
        profesorEdt->clear();
        reloadData(service.filterByProfesor(profesor));
    }catch(EmptyListError& err) {
        QMessageBox::warning(this,"Error",QString::fromStdString(err.getMessage()));
    }
}

void DisciplinaGui::undoGUI() {
    try {
        service.undo();
        reloadData(service.getDisciplineList());
        QMessageBox::information(this,"Info",QString::fromStdString("Undo Realizat cu Succes"));
    } catch(const Error& err) {
        QMessageBox::warning(this,"Error",QString::fromStdString(err.getMessage()));
    }
}

void DisciplinaGui::raportGUI() {
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
void DisciplinaGui::addDisciplinaToContractGUI() {
    try {
        const string den = contractDenEdit->text().toStdString();
        contractDenEdit->clear();
        service.addDisciplinaContract(den);
        reloadContractData(service.contractList());
        QMessageBox::information(this,"Info",QString::fromStdString("Disciplina adaugata cu succes"));

    }catch (InvalidDenumire& err) {
        QMessageBox::warning(this,"Error",QString::fromStdString(err.getMessage()));
    }catch (Error& err) {
        QMessageBox::warning(this,"Error",QString::fromStdString(err.getMessage()));
    }
}
void DisciplinaGui::clearContractGUI() {
    service.emptyContract();
    reloadContractData(service.contractList());

}
void DisciplinaGui::populateContractGUI() {
    try {
        const int nr_discipline = contractNrEdit->text().toInt();
        contractNrEdit->clear();
        service.populateContract(nr_discipline);
        reloadContractData(service.contractList());
    } catch(InvalidGenerateNumber& err) {
        QMessageBox::warning(this,"Error",QString::fromStdString(err.getMessage()));
    }

}
void DisciplinaGui::exportToCsvGUI() {
    try {
        const string filename = contractFileNameEdit->text().toStdString();
        contractFileNameEdit->clear();
        service.exportCSV(filename);
    }catch(InvalidFileError& err) {
        QMessageBox::warning(this,"Error",QString::fromStdString(err.getMessage()));
    }

}
void DisciplinaGui::exportToHtmlGUI() {
    try {
        const string filename = contractFileNameEdit->text().toStdString();
        contractFileNameEdit->clear();
        service.exportHTML(filename);
    }catch(InvalidFileError& err) {
        QMessageBox::warning(this,"Error",QString::fromStdString(err.getMessage()));
    }

}