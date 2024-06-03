//
// Created by horatiu on 5/19/24.
//

#include "ProdusGui.h"
#include <QHBoxLayout>
#include <QFormLayout>

void ProdusGui::initGUI() {
    auto* lyMain = new QHBoxLayout{};
    this->setLayout(lyMain);

    auto* left = new QWidget{};
    auto* lyLeft = new QVBoxLayout{};
    left->setLayout(lyLeft);

    auto* form1 =new QWidget{};
    auto* lyForm1 = new QFormLayout{};
    form1->setLayout(lyForm1);
    editPret = new QLineEdit{};
    lyForm1->addRow(labelPret,editPret);
    lyForm1->addWidget(buttonPret);
    lyLeft->addWidget(form1);

    auto* form2 =new QWidget{};
    auto* lyForm2 = new QFormLayout{};
    form2->setLayout(lyForm2);
    editNume = new QLineEdit{};
    lyForm2->addRow(labelNume,editNume);
    lyForm2->addWidget(buttonNume);
    lyLeft->addWidget(form2);

    auto* right = new QWidget{};
    auto* lyRight = new QVBoxLayout{};
    right->setLayout(lyRight);

    table = new QTableWidget(10,3);
    QStringList header;
    header<<"Nume"<<"Firma"<<"Pret";
    table->setHorizontalHeaderLabels(header);

    lyRight->addWidget(table);


    lyMain->addWidget(left);
    lyMain->addWidget(right);

}

void ProdusGui::connectSlots() {
    QObject::connect(buttonPret,&QPushButton::pressed,this,[&](){
        float pret = editPret->text().toFloat();
        editPret->clear();
        reloadData(serv.filterByPret(pret));
    });
    QObject::connect(buttonNume,&QPushButton::pressed,this,[&](){
        std::string nume = editNume->text().toStdString();
        editNume->clear();
        reloadData(serv.filterByName(nume));
    });
}


void ProdusGui::reloadData(const std::vector<Produs>& lst) {

    table->clearContents();
    table->setRowCount((int)lst.size());
    int n = 0;
    for(auto& p : lst){
        table->setItem(n,0,new QTableWidgetItem(QString::fromStdString(p.getNume())));
        table->setItem(n,1,new QTableWidgetItem(QString::fromStdString(p.getFirma())));
        table->setItem(n,2,new QTableWidgetItem(QString::number(p.getPret())));
        n++;
    }

}