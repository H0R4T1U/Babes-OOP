//
// Created by horatiu on 6/15/24.
//

#include <QHBoxLayout>
#include <QFormLayout>
#include "Gui.h"
#include <QLineEdit>
#include <QDebug>
#include <QPainter>

void Gui::initGui() {
    auto* lyMain = new QHBoxLayout{};
    this->setLayout(lyMain);
    auto* lyLeft = new QVBoxLayout{};
    auto* left = new QWidget{};
    auto* lyRight = new QVBoxLayout{};
    auto* right = new QWidget{};
    auto* lyForm1 = new QFormLayout{};
    auto* form1 = new QWidget{};
    form1->setLayout(lyForm1);
    lyLeft->addWidget(form1);
    table = new QTableView{};
    model = new MelodieTableModel{table};
    table->setModel(model);
    lyRight->addWidget(table);
    idedt = new QLineEdit{};
    autoredt = new QLineEdit{};
    denedt = new QLineEdit{};
    tipedt = new QLineEdit{};
    lyForm1->addRow(idlbl,idedt);
    lyForm1->addRow(denlbl,denedt);
    lyForm1->addRow(autorlbl,autoredt);
    lyForm1->addRow(tiplbl,tipedt);
    lyForm1->addWidget(adaugaBtn);
    lyForm1->addWidget(deleteBtn);

    right->setLayout(lyRight);
    left->setLayout(lyLeft);
    lyMain->addWidget(left);
    lyMain->addWidget(right);
}
void Gui::connectSlots() {
    QObject::connect(adaugaBtn,&QPushButton::pressed,this,[&](){
        int id = idedt->text().toInt();
        string titlu = denedt->text().toStdString();
        string artist = autoredt->text().toStdString();
        string tip = tipedt->text().toLower().toStdString();
        idedt->clear();
        denedt->clear();
        autoredt->clear();
        tipedt->clear();
        service.add(id,titlu,artist,tip);
        reloadData();
    });
    QObject::connect(deleteBtn,&QPushButton::pressed,this,[&](){
        auto rows = table->selectionModel()->selectedRows();
        if(!rows.isEmpty()){
            auto i = table->selectionModel()->selectedRows().at(0);
            int row = i.row();
            service.remove(service.sortArt().at(row).getTitlu());
            reloadData();
        }

        return;
    });
}
// reincarca tabel
void Gui::reloadData() {
    model->setList(service.sortArt());
    this->repaint();
}

void Gui::paintEvent(QPaintEvent *event) {
    QPainter p{this};
    map<string,int> tipuri = service.getNrTypes();
    int r = 4;
    for(int i = 0 ; i<tipuri["rock"];i++){
        p.drawEllipse(20,20,20+r,20+r);
        r+=4;
    }
    r=4;
    for(int i = 0 ; i<tipuri["pop"];i++){
        p.drawEllipse(20,this->height()-20,20+r,20+r);
        r+=4;
    }
    r=4;
    for(int i = 0 ; i<tipuri["disco"];i++){
        p.drawEllipse(this->width()-20,20,20+r,20+r);
        r+=4;
    }
    r=4;
    for(int i = 0 ; i<tipuri["folk"];i++){
        p.drawEllipse(this->width()-20,this->height()-20,20+r,20+r);
        r+=4;
    }
}
