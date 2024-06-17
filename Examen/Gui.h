//
// Created by horatiu on 6/16/24.
//

#ifndef EXAMEN_GUI_H
#define EXAMEN_GUI_H


#include "Service.h"
#include <QWidget>
#include <QTableWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
class Gui: public QWidget, public Observer {
private:
    // Service
    Service& service;
    //tabela
    QTableWidget* table{};
    QPushButton* reset = new QPushButton{"Reset"};
    // Adaugare
    QLabel* idLbl = new QLabel{"Id:"};
    QLabel* denLbl = new QLabel{"Denumire:"};
    QLabel* stareLbl = new QLabel{"Stare:"};
    QLabel* programator1Lbl = new QLabel{"Programator 1:"};
    QLabel* programator2Lbl = new QLabel{"Programator 2:"};
    QLabel* programator3Lbl = new QLabel{"Programator 3:"};
    QLabel* programator4Lbl = new QLabel{"Programator 4:"};
    QLineEdit* idEdt{},*denEdt{},*stareEdt{},*programator1Edt{},*programator2Edt{},*programator3Edt{},*programator4Edt{};
    QPushButton* add = new QPushButton{"Adauga!"};
    // Cautare
    QLabel* searchLbl = new QLabel{"Programator:"};
    QLineEdit* searchEdt{};
    QPushButton* cauta = new QPushButton{"Cauta"};

public:
    // initializeaza elemente
    void initGui();
    // conecteaza semnale-slot
    void connectSlots();
    // suprascriem functia update pur virtuala
    void update()override;
    // reincarcam datele
    void reloadData(vector<Task>list);
    // Constructor gui
    Gui(Service&s):service{s}{
        initGui();
        connectSlots();
        reloadData(service.sortStare());
    };
    // Destructor Gui
    ~Gui(){
        service.deleteObserver(this);
    }
};


#endif //EXAMEN_GUI_H
