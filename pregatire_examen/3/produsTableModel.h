//
// Created by horatiu on 6/14/24.
//

#ifndef INC_3_PRODUSTABLEMODEL_H
#define INC_3_PRODUSTABLEMODEL_H

#include <QAbstractTableModel>
#include "Produs.h"
#include "Gui.h"
class Gui;
class produsTableModel: public QAbstractTableModel {
private:
    vector<Produs> list;
    Gui* ui;
public:

    produsTableModel(QObject* parrent,Gui* ui);
    QVariant data(const QModelIndex&,int role)const override;
    int rowCount(const QModelIndex& par = QModelIndex())const noexcept override;
    int columnCount(const  QModelIndex& par = QModelIndex())const noexcept override;
    QVariant headerData(int section,Qt::Orientation orientation,int role) const override;
    void setList(const vector<Produs>&_list);
    int nr_vocale(string nume) const;
};


#endif //INC_3_PRODUSTABLEMODEL_H
