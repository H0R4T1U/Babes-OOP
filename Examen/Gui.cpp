//
// Created by horatiu on 6/16/24.
//

#include "Gui.h"
#include <QHBoxLayout>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QStringList>
#include <QMessageBox>
void Gui::initGui() {
    auto* lyMain = new QHBoxLayout{};
    auto* left = new QWidget{};
    auto* right = new QWidget{};
    auto* lyLeft = new QVBoxLayout{};
    auto* lyRight = new QVBoxLayout{};
    auto* lyForm = new QFormLayout{};
    auto* form = new QWidget{};
    // Partea stanga
    // Adaugare
    idEdt = new QLineEdit{};
    denEdt = new QLineEdit{};
    stareEdt = new QLineEdit{};
    programator1Edt = new QLineEdit{};
    programator2Edt = new QLineEdit{};
    programator3Edt = new QLineEdit{};
    programator4Edt = new QLineEdit{};
    lyForm->addRow(idLbl,idEdt);
    lyForm->addRow(denLbl,denEdt);
    lyForm->addRow(programator1Lbl,programator1Edt);
    lyForm->addRow(programator2Lbl,programator2Edt);
    lyForm->addRow(programator3Lbl,programator3Edt);
    lyForm->addRow(programator4Lbl,programator4Edt);
    lyForm->addRow(stareLbl,stareEdt);
    lyForm->addWidget(add);
    // Cautare
    searchEdt = new QLineEdit{};
    lyForm->addRow(searchLbl,searchEdt);
    lyForm->addWidget(cauta);
    // Partea dreapta
    table = new QTableWidget{10,4};
    QStringList  headerData;
    headerData<<"Id"<<"Denumire"<<"Programatori"<<"stare";
    table->setHorizontalHeaderLabels(headerData);
    lyRight->addWidget(reset);


    this->setLayout(lyMain);
    right->setLayout(lyRight);
    left->setLayout(lyLeft);
    form->setLayout(lyForm);
    lyLeft->addWidget(form);
    lyRight->addWidget(table);
    lyMain->addWidget(left);
    lyMain->addWidget(right);

}

void Gui::update() {
    reloadData(service.sortStare());
}

void Gui::reloadData(vector<Task> list) {
    table->setRowCount((int)list.size());
    int n=0;
    for(auto& x : list){
        table->setItem(n,0,new QTableWidgetItem{QString::number(x.getId())});
        table->setItem(n,1,new QTableWidgetItem{QString::fromStdString(x.getDescriere())});
        string prog;
        for(auto& p: x.getProgramatori()){
            prog += p + " ";
        };
        table->setItem(n,2,new QTableWidgetItem{QString::fromStdString(prog)});
        table->setItem(n,3,new QTableWidgetItem{QString::fromStdString(x.getStare())});
        n++;
    }
}

void Gui::connectSlots() {
    service.addObserver(this);
    QObject::connect(reset,&QPushButton::pressed,this,[&](){
        reloadData(service.sortStare());
    });
    QObject::connect(cauta,&QPushButton::pressed,this,[&](){
        string prog = searchEdt->text().toStdString();
        if(!prog.empty()){
            reloadData(service.filter(prog));
        }
    });
    QObject::connect(add,&QPushButton::pressed,this,[&](){
        int id = idEdt->text().toInt();
        string den = denEdt->text().toStdString();
        string stare = stareEdt->text().toLower().toStdString();
        vector<string> programatori;
        if(!programator1Edt->text().isEmpty()){
            programatori.push_back(programator1Edt->text().toStdString());
        }
        if(!programator2Edt->text().isEmpty()){
            programatori.push_back(programator2Edt->text().toStdString());
        }
        if(!programator3Edt->text().isEmpty()){
            programatori.push_back(programator3Edt->text().toStdString());
        }
        if(!programator4Edt->text().isEmpty()){
            programatori.push_back(programator4Edt->text().toStdString());
        }
        idEdt->clear();
        denEdt->clear();
        stareEdt->clear();
        programator1Edt->clear();
        programator2Edt->clear();
        programator3Edt->clear();
        programator4Edt->clear();
        try{
            service.add(id,den,programatori,stare);
        }catch(exception& ex){
            QMessageBox::information(this,"Warning",QString::fromStdString(ex.what()));
        }
    });

}


