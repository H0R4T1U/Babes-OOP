//
// Created by horatiu on 6/14/24.
//

#include <QHBoxLayout>
#include "Gui.h"
#include <QStringList>
#include <QFormLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QPainter>
void Gui::initGui() {
    auto* lyMain = new QHBoxLayout{};
    this->setLayout(lyMain);
    auto* left = new QWidget{};
    auto lyLeft = new QVBoxLayout{};
    auto* right = new QWidget{};
    auto* lyRight = new QVBoxLayout{};
    left->setLayout(lyLeft);
    auto* form1 = new QWidget;
    auto* lyForm1 = new QFormLayout{};
    denEdt = new QLineEdit{};
    idEdt = new QLineEdit{};
    tipEdt  = new QLineEdit{};
    rotiEdt  = new QLineEdit{};
    form1->setLayout(lyForm1);
    lyForm1->addRow(idLbl,idEdt);
    lyForm1->addRow(denLbl,denEdt);
    lyForm1->addRow(tipLbl,tipEdt);
    lyForm1->addRow(rotiLbl,rotiEdt);
    lyForm1->addWidget(adaugaBut);
    tipuri = new QComboBox{};
    lyForm1->addWidget(tipuri);
    lyLeft->addWidget(form1);

    right->setLayout(lyRight);
    int n = 4;
    int m = 10;
    table = new QTableWidget(m,n);
    QStringList headers;
    headers<<"Id"<<"Denumire"<<"Tip"<<"Nr Roti";
    table->setHorizontalHeaderLabels(headers);
    lyRight->addWidget(table);

    lyMain->addWidget(left);
    lyMain->addWidget(right);
}
void Gui::update() {
    reloadCombo();
    reloadData();
}
void Gui::reloadData() {
    table->clearContents();
    vector<Tractor> list = service.sortDen();
    table->setRowCount((int)list.size());

    int n= 0 ;
    for(auto& x : list){

        auto* idItem = new QTableWidgetItem(QString::number(x.getId()));
        auto* denumireItem = new QTableWidgetItem(QString::fromStdString(x.getDenumire()));
        auto* tipItem = new QTableWidgetItem(QString::fromStdString(x.getTip()));
        auto* rotiItem = new QTableWidgetItem(QString::number(x.getRoti()));
        if(x.getTip() == tipuri->currentText().toStdString()){
            idItem->setBackground(QBrush(QColor(Qt::red)));
            denumireItem->setBackground(QBrush(QColor(Qt::red)));
            tipItem->setBackground(QBrush(QColor(Qt::red)));
            rotiItem->setBackground(QBrush(QColor(Qt::red)));
        }
        table->setItem(n, 0, idItem);
        table->setItem(n, 1, denumireItem);
        table->setItem(n, 2, tipItem);
        table->setItem(n, 3, rotiItem);
        n++;
    }
}

Gui::Gui(Service &service): service{service} {
    initGui();
    reloadCombo();
    reloadData();
    connectSlots();
}

void Gui::connectSlots() {
    service.addObserver(this);
    QObject::connect(table,&QTableWidget::cellPressed,this,[&](){
        repaint();
    });
    QObject::connect(adaugaBut,&QPushButton::pressed,this,[&](){
    try {
        int id = idEdt->text().toInt();
        idEdt->clear();
        string den = denEdt->text().toStdString();
        denEdt->clear();
        string tip = tipEdt->text().toStdString();
        tipEdt->clear();
        int roti = rotiEdt->text().toInt();
        rotiEdt->clear();
        service.add(id,den,tip,roti);
    }catch(exception&ex){
        QMessageBox::information(this,"Warning",ex.what());
    }
    QObject::connect(tipuri,&QComboBox::currentTextChanged,this,[&](){
        reloadData();
    });
    });

}

void Gui::reloadCombo() {
    tipuri->clear();
    vector<string> t = service.tipuri();
    for(auto& x:t){
        tipuri->addItem(QString::fromStdString(x));
    }
}

void Gui::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    auto ind = table->selectionModel()->selectedRows();
    if(!ind.isEmpty()){
        int row = table->selectionModel()->selectedRows().at(0).row();
        Tractor t = service.sortDen().at(row);
        int roti = t.getRoti();
        int x=-20;
        for(int i = 0; i <roti;i++){
            x+= 100;
            p.drawEllipse(x,this->height()-100,50,50);
        }


    }

}
