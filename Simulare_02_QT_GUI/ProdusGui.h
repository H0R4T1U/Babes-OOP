//
// Created by horatiu on 5/19/24.
//

#ifndef SIMULARE_02_PRODUSGUI_H
#define SIMULARE_02_PRODUSGUI_H


#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include "Service.h"

class ProdusGui : public QWidget {
private:
    Service serv;
    QTableWidget* table{};
    QLabel* labelPret = new QLabel("PRET:");
    QLabel* labelNume = new QLabel("NUME");
    QLineEdit* editPret{};
    QLineEdit* editNume{};
    QPushButton* buttonPret = new QPushButton{"Filtreaza dupa pret!"};
    QPushButton* buttonNume= new QPushButton{"Filtreaza dupa Nume!"};
public:
    void initGUI();
    void connectSlots();
    void reloadData(const std::vector<Produs>&);
    ProdusGui(const Service& pS): serv{pS}{
        initGUI();
        connectSlots();
        reloadData(serv.serviceGetLista());
    };
};


#endif //SIMULARE_02_PRODUSGUI_H
