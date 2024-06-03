//
// Created by horatiu on 5/31/24.
//

#ifndef LABORATOR_14_OOP_DISCIPLINALISTMODEL_H
#define LABORATOR_14_OOP_DISCIPLINALISTMODEL_H


#include <QtWidgets/QListWidget>
#include <QAbstractListModel>
#include <QAbstractTableModel>
#include "Disciplina.h"
#include <vector>
using namespace std;

class DisciplinaListModel : public QAbstractTableModel
{
private:
    // vectorul curent de masini
    vector<Disciplina> disciplinaList;
public:

    // constructorul clasei model
    DisciplinaListModel(QObject* parent);

    // suprascriem metoda data pentru a afisa datele unei discipline
    QVariant data(const QModelIndex& index, int role) const override;

    // suprascriem metoda rowCount ca sa returneze corect pentru tabelul nostru
    int rowCount(const QModelIndex& parent = QModelIndex()) const noexcept override;

    // suprascriem metoda columnCount ca sa returneze corect pentru tabelul nostru
    int columnCount(const QModelIndex& parent = QModelIndex()) const noexcept override;

    // suprascriem metoda headerData ca sa afiseze antetul corespunzator
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    // punem lista corespunzatoare
    void setList(const vector<Disciplina>& _disciplinaList);
};

#endif //LABORATOR_14_OOP_DISCIPLINALISTMODEL_H
