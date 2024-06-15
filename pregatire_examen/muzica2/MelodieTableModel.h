//
// Created by horatiu on 6/15/24.
//

#ifndef MUZICA2_MELODIETABLEMODEL_H
#define MUZICA2_MELODIETABLEMODEL_H
#include <QAbstractTableModel>
#include "Melodie.h"

class MelodieTableModel:public QAbstractTableModel {
private:
    // vector cu melodii
    vector<Melodie> list;
public:
    // constructor tablemodel
    explicit MelodieTableModel(QObject *parent );
    // suprascriem metoda data din Q\QAbstractTableModel
    QVariant data(const QModelIndex &index, int role) const override;
    // SUPRASCRIEM METODA rowCount din QAbstractTableModel
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    // Suprascriem metoda ColumnCount din QAbstractTableModel
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    // Suprascriem metoda HeaderData din QAbstractTableModel
    QVariant headerData(int section, Qt::Orientation orientation,int role) const override;
    // setam lista si initalizam model
    void setList(const vector<Melodie>& _list);
    // returneaza nr de piese a artistului din lista
    int nrAutor(const string& artist)const;
    // returneaza nr de piese de tip x din lista;
    int nrGen(const string& tip)const;
};


#endif //MUZICA2_MELODIETABLEMODEL_H
