//
// Created by horatiu on 6/14/24.
//

#include "produsTableModel.h"

produsTableModel::produsTableModel(QObject *parrent,Gui* ui) : QAbstractTableModel(parrent) {
    this->ui = ui;
}

QVariant produsTableModel::data(const QModelIndex &index, int role) const {
    const int row = index.row();
    const int column = index.column();
    if(role == Qt::DisplayRole){
        switch(column){
            case 0: return QString::number(list.at(row).getId());
            case 1: return QString::fromStdString(list.at(row).getNume());
            case 2: return QString::fromStdString(list.at(row).getTip());
            case 3: return QString::number(list.at(row).getPret());
            case 4:return QString::number(nr_vocale(list.at(row).getNume()));
        }
        return QString("R%1, C%2").arg(index.row()+1,index.column()+1);

    }
    if(role == Qt::BackgroundRole){
       if(list.at(row).getPret() <= ui->sliderFilt->value()){
           return QBrush("red");
       }
   }
    return QVariant();

}

int produsTableModel::nr_vocale(std::string nume) const {
    int nr = 0;
    for(auto& x:nume){
        switch(x){
            case 'a':
            case 'A':
                nr++;break;
            case 'e':
            case 'E':
                nr++;break;
            case 'i':
            case 'I':
                nr++;break;
            case 'o':
            case 'O':
                nr++;break;
            case 'u':
            case 'U':
                nr++;break;
        }
    }
    return nr;
}

int produsTableModel::rowCount(const QModelIndex &par) const noexcept {
    return (int)list.size();
}

int produsTableModel::columnCount(const QModelIndex &par) const noexcept {
    return 5;
}

QVariant produsTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if(role == Qt::DisplayRole){
        if(orientation == Qt::Horizontal){
            switch(section) {
                case 0: return QString("ID");
                case 1: return QString("Titlu");
                case 2: return QString("TIp");
                case 3: return QString("Pret");
                case 4: return QString("Nr Vocale");
            }
            return QString("col %1").arg(section);
        }else{
            return QString("%1").arg(section);
        }

    }
    return QVariant();
}

void produsTableModel::setList(const vector<Produs>&  _list) {
    list = _list;

    const QModelIndex topLeft = createIndex(0,0);
    const QModelIndex bottomRight = createIndex(rowCount(), columnCount());
    dataChanged(topLeft,bottomRight);
    layoutChanged();
}


