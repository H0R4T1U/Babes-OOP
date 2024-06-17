//
// Created by horatiu on 6/16/24.
//
#include <QTableWidget>
#include "ferestre.h"
#include <QHBoxLayout>
void Ferestre::initGui() {
    auto* lyMain =new  QHBoxLayout{};
    this->setLayout(lyMain);
    this->setWindowTitle(QString::fromStdString(stare));
    table = new QTableWidget{10,4};
    QStringList  headerData;
    headerData<<"Id"<<"Denumire"<<"Programatori"<<"stare";
    table->setHorizontalHeaderLabels(headerData);
    lyMain->addWidget(table);
    lyMain->addWidget(open);
    lyMain->addWidget(closed);
    lyMain->addWidget(inprogress);
};

void Ferestre::reloadData(vector<Task> list) {
        table->setRowCount((int)list.size());
        int n=0;
        for(auto& x : list) {
            if (x.getStare() == stare) {
                table->setItem(n, 0, new QTableWidgetItem{QString::number(x.getId())});
                table->setItem(n, 1, new QTableWidgetItem{QString::fromStdString(x.getDescriere())});
                string prog;
                for (auto &p: x.getProgramatori()) {
                    prog += p + " ";
                };
                table->setItem(n, 2, new QTableWidgetItem{QString::fromStdString(prog)});
                table->setItem(n, 3, new QTableWidgetItem{QString::fromStdString(x.getStare())});
                n++;
            }
        }
        table->setRowCount(n);
    }

void Ferestre::update() {
    reloadData(service.sortStare());
}

void Ferestre::conectSlots() {
    service.addObserver(this);
    QObject::connect(open,&QPushButton::pressed,this,[&](){
       if(!table->selectionModel()->selectedRows().isEmpty()) {
           int row = table->selectionModel()->selectedRows().at(0).row();
           vector<Task> filtered;
           vector<Task> list = service.sortStare();
           copy_if(list.begin(),list.end(), back_inserter(filtered),[&](Task& t1){
               return t1.getStare() == stare;
           });
           string den = filtered.at(row).getDescriere();
           string st = "open";
           service.modifyStare(den,st);
       }
    });
    QObject::connect(closed,&QPushButton::pressed,this,[&](){
        if(!table->selectionModel()->selectedRows().isEmpty()) {
            int row = table->selectionModel()->selectedRows().at(0).row();
            vector<Task> filtered;
            vector<Task> list = service.sortStare();
            copy_if(list.begin(),list.end(), back_inserter(filtered),[&](Task& t1){
                return t1.getStare() == this->stare;
            });
            string den = filtered.at(row).getDescriere();
            string st = "closed";
            service.modifyStare(den,st);
        }
    });
    QObject::connect(inprogress,&QPushButton::pressed,this,[&](){
        if(!table->selectionModel()->selectedRows().isEmpty()) {
            int row = table->selectionModel()->selectedRows().at(0).row();
            vector<Task> filtered;
            vector<Task> list = service.sortStare();
            copy_if(list.begin(),list.end(), back_inserter(filtered),[&](Task& t1){
                return t1.getStare() == stare;
            });
            string den = filtered.at(row).getDescriere();
            string st = "inprogress";
            service.modifyStare(den,st);
        }
    });
}




