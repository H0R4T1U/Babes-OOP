//
// Created by horatiu on 6/15/24.
//

#include "MelodieTableModel.h"

int MelodieTableModel::rowCount(const QModelIndex &parent) const {
    return (int)list.size();
}

int MelodieTableModel::columnCount(const QModelIndex &parent) const {
    return 6;
}

QVariant MelodieTableModel::data(const QModelIndex &index, int role) const {
    int row = index.row();
    int column = index.column();
    if(role == Qt::DisplayRole){
        switch (column) {
            case 0: return QString::number(list.at(row).getId());
            case 1: return QString::fromStdString(list.at(row).getTitlu());
            case 2: return QString::fromStdString(list.at(row).getArtist());
            case 3: return QString::fromStdString(list.at(row).getTip());
            case 4: return QString::number(nrAutor(list.at(row).getArtist()));
            case 5: return QString::number(nrGen(list.at(row).getTip()));

        }
        return QString("R%1, C%2").arg(index.row()+1,index.column()+1);
    }
    return QVariant();
}

int MelodieTableModel::nrAutor(const string &artist)const {
    int nr = 0;
    for(auto& x: list){
        if(x.getArtist() == artist){
            nr++;
        }
    }
    return nr;
}

int MelodieTableModel::nrGen(const string &tip)const {
    int nr = 0;
    for(auto& x : list){
        if(x.getTip() == tip){
            nr++;
        }
    }
    return nr;
}

QVariant MelodieTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if(role == Qt::DisplayRole){
        if(orientation == Qt::Horizontal){
            switch (section) {
                case 0: return QString("Id");
                case 1: return QString("Titlu");
                case 2: return QString("Artist");
                case 3: return QString("Tip");
                case 4: return QString("Nr piese Artist");
                case 5: return QString("Nr piese Gen");
            }
            return QString("col %1").arg(section);
        }else{
            return QString("%1").arg(section);
        }
    }
    return QVariant();
}

void MelodieTableModel::setList(const vector<Melodie> &_list) {
    this->list = _list;
    auto topleft = createIndex(0,0);
    auto bottomRight = createIndex(rowCount(), columnCount());
    dataChanged(topleft,bottomRight);
    layoutChanged();
}

MelodieTableModel::MelodieTableModel(QObject *parent) : QAbstractTableModel(parent) {}
