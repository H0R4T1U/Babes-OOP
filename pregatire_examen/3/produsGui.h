//
// Created by horatiu on 6/14/24.
//

#ifndef INC_3_PRODUSGUI_H
#define INC_3_PRODUSGUI_H


#include <QWidget>
#include "Observer.h"
#include "Service.h"
#include <QLabel>
class produsGui: public QWidget,public Observer {
private:
    Service& service;
    QLabel* nrProd = new QLabel{};
    string tip;
public:
    produsGui(Service& serv,const string& prod):service{serv},tip{prod}{
        initGui();
        connectSlots();
    };
    ~produsGui() override{
        service.removeObserver(this);
    }
    void update()override;
    void connectSlots();
    void initGui();
};


#endif //INC_3_PRODUSGUI_H
