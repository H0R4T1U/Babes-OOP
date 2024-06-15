//
// Created by horatiu on 6/14/24.
//

#ifndef INC_2_GUI_H
#define INC_2_GUI_H


#include <QWidget>
#include "Service.h"
#include <QTableWidget>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>

class Gui: public QWidget, public Observer {
private:
    Service service;
    QTableWidget* table = new QTableWidget{};
    QLabel* denLbl = new QLabel("Denumire:");
    QLabel* idLbl = new QLabel("Id:");
    QLabel* tipLbl = new QLabel("Tip:");
    QLabel* rotiLbl = new QLabel("Nr roti:");
    QLineEdit* denEdt{},*idEdt{},*tipEdt{},*rotiEdt{};
    QPushButton* adaugaBut = new QPushButton("Adauga Tractor");
    QComboBox* tipuri =  new QComboBox{};
public:
    explicit Gui(Service& service);
    void connectSlots();
    void initGui();
    void update() override;
    void reloadCombo();
    void paintEvent(QPaintEvent *event) override;
    void reloadData();
};


#endif //INC_2_GUI_H
