//
// Created by horatiu on 6/14/24.
//

#ifndef INC_3_GUI_H
#define INC_3_GUI_H


#include <QWidget>
#include <QTableView>
#include "Service.h"
#include "produsTableModel.h"
#include <QLabel>
#include <QPushButton>
#include "produsGui.h"
class produsTableModel;
class Gui: public QWidget,public Observer {
private:
    vector<produsGui*> guis;
    Service &service;
    QTableView* table{};
    produsTableModel* model{};
    QLabel* pretlbl = new QLabel{"Pret:"};
    QLabel* filtlbl = new QLabel{"Pret:"};
    QLabel* idlbl = new QLabel{"Id:"};
    QLabel* numelbl = new QLabel{"Nume:"};
    QLabel* tiplbl = new QLabel{"Tip:"};
    QLineEdit* idedt{},*pretedt{},*numedt{},*tipedt{};
    QPushButton* adaugabtn = new QPushButton{"Adauga"};

public:

    QSlider* sliderFilt = new QSlider{};

    void initGui();
    void connectSlots();
    void reloadData();
    void update() override;
    void colorTable(vector<Produs>list);
    explicit Gui(Service& serv): service{serv}{
        initGui();
        connectSlots();
        reloadData();
    }
    ~Gui(){
        service.removeObserver(this);
    }
};


#endif //INC_3_GUI_H
