//
// Created by horatiu on 6/14/24.
//

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include "Gui.h"
#include <QLineEdit>
#include <QMessageBox>
void Gui::update() {
    reloadData();
}

void Gui::reloadData() {
    model->setList(service.sortPret());
}

void Gui::connectSlots() {
    service.addObserver(this);
    QObject::connect(adaugabtn,&QPushButton::pressed,this,[&](){
        try{
            int id = idedt->text().toInt();
            string nume = numedt->text().toStdString();
            string tip = tipedt->text().toStdString();
            double pret = pretedt->text().toDouble();
            idedt->clear();
            numedt->clear();
            tipedt->clear();
            pretedt->clear();
            service.add(id,nume,tip,pret);
        }catch(exception&ex){
            QMessageBox::information(this,"Warning",QString::fromStdString(ex.what()));
        }
    });
    QObject::connect(sliderFilt,&QSlider::valueChanged,this,[&](){
        reloadData();
    });

}

void Gui::initGui() {
    auto* lyMain = new QHBoxLayout{};
    auto* left = new QWidget{};
    auto* lyLeft = new QVBoxLayout{};
    auto* right = new QWidget{};
    auto* lyRight = new QVBoxLayout{};
    auto* form1 = new QWidget{};
    auto* lyForm1 = new QFormLayout{};
    form1->setLayout(lyForm1);
    idedt = new QLineEdit{};
    pretedt = new QLineEdit{};
    numedt = new QLineEdit{};
    tipedt = new QLineEdit{};
    lyForm1->addRow(idlbl,idedt);
    lyForm1->addRow(numelbl,numedt);
    lyForm1->addRow(tiplbl,tipedt);
    lyForm1->addRow(pretlbl,pretedt);
    lyForm1->addWidget(adaugabtn);
    sliderFilt->setMinimum(0);
    sliderFilt->setMaximum(100);
    lyForm1->addRow(filtlbl,sliderFilt);
    lyRight->addWidget(form1);
    table = new QTableView{};
    model = new produsTableModel(table,this);
    table->setModel(model);
    lyLeft->addWidget(table);

    right->setLayout(lyRight);
    left->setLayout(lyLeft);
    this->setLayout(lyMain);
    lyMain->addWidget(left);
    lyMain->addWidget(right);

    for(auto& x : service.tipuri()){
        auto* p = new produsGui{service,x};
        p->show();
        guis.push_back(p);
    }
}


