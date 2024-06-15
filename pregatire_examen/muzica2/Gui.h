//
// Created by horatiu on 6/15/24.
//

#ifndef MUZICA2_GUI_H
#define MUZICA2_GUI_H


#include "Service.h"
#include <QTableView>
#include <QLabel>
#include <QPushButton>
#include "MelodieTableModel.h"
class Gui: public QWidget {
private:
    // service melodii
    Service& service;
    // table view pt tabel melodii
    QTableView* table = new QTableView{};
    // model pt table pt melodii
    MelodieTableModel* model{};
    // label id
    QLabel* idlbl = new QLabel{"id"};
    // label den
    QLabel* denlbl = new QLabel{"titlu:"};
    // label autor
    QLabel* autorlbl = new QLabel{"autor:"};
    // label tip
    QLabel* tiplbl = new QLabel{"tip:"};
    // line edituri pentru id,autor,den,tip
    QLineEdit* idedt{},*autoredt{},*denedt{},*tipedt{};
    // button adaugare melodie
    QPushButton* adaugaBtn = new QPushButton{"Adauga"};
    // button stergere melodie
    QPushButton* deleteBtn = new QPushButton{"Delete"};
public:
    // metoda initializare gui
    void initGui();
    // metoda conectare butoanele la semnale
    void connectSlots();
    // metoda reincarcare lista
    void reloadData();
    void paintEvent(QPaintEvent *event) override;
    // constructor gui primeste service prin referinta si intializeaza
    explicit Gui(Service& service):service{service}{
        initGui();
        connectSlots();
        reloadData();

    }
};


#endif //MUZICA2_GUI_H
