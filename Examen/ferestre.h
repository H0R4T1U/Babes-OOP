//
// Created by horatiu on 6/16/24.
//

#ifndef EXAMEN_FERESTRE_H
#define EXAMEN_FERESTRE_H


#include <QWidget>
#include <QLabel>
#include "Observer.h"
#include "Service.h"
#include <QTableWidget>
#include <QPushButton>

class Ferestre: public QWidget, public Observer{
private:
    // Service
    Service& service;
    // starea ferestrei
    string stare;
    // tabel cu task-uri
    QTableWidget* table;
    // butoane stare
    QPushButton* open = new QPushButton{"open"};
    QPushButton* closed = new QPushButton{"closed"};
    QPushButton* inprogress = new QPushButton{"inprogress"};

public:
    // initializam gui
    void initGui();
    // conectam semnale->slot
    void conectSlots();
    // suprascriem update
    void update();
    // reincarcam date
    void reloadData(vector<Task>);
    // Constructor Ferestere
    Ferestre(Service& service,const string& stare): service{service},stare{stare}{
        initGui();
        conectSlots();
        reloadData(service.sortStare());
    };
    // Destructor Ferestre
    ~Ferestre(){
        service.deleteObserver(this);
    }
};


#endif //EXAMEN_FERESTRE_H
