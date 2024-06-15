//
// Created by horatiu on 6/14/24.
//

#include "produsGui.h"
#include <QHBoxLayout>
void produsGui::initGui() {
    auto* lyMain = new QHBoxLayout{};
    this->setLayout(lyMain);
    lyMain->addWidget(nrProd);
    this->setWindowTitle(QString::fromStdString(tip));
    nrProd->setText(QString::number(service.nrProdTip(tip)));
}

void produsGui::update() {
    nrProd->setText(QString::number(service.nrProdTip(tip)));
}

void produsGui::connectSlots() {
    service.addObserver(this);
}
