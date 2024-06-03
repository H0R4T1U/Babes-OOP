#include "disciplinaListModel.h"
#include <QMessageBox>

DisciplinaListModel::DisciplinaListModel(QObject* parent) : QAbstractTableModel(parent) {};

QVariant DisciplinaListModel::data(const QModelIndex& index, int role) const
{
    const int row = index.row();
    const int column = index.column();
    if (role == Qt::DisplayRole)
    {
        switch (column)
        {
            case 0: return QString::fromStdString(disciplinaList.at(row).getDenumire());
            case 1: return QString::number(disciplinaList.at(row).getOre());
            case 2: return QString::fromStdString(disciplinaList.at(row).getTip());
            case 3: return QString::fromStdString(disciplinaList.at(row).getProfesor());

        }
        //return QString("col %1").arg(column);
        return QString("R%1, C%2").arg(index.row() + 1).arg(index.column() + 1);
    }
    return QVariant();

}

int DisciplinaListModel::rowCount(const QModelIndex&) const noexcept
{
    return (int)(disciplinaList.size());
}
int DisciplinaListModel::columnCount(const QModelIndex&) const noexcept
{
    return 4;
}

QVariant DisciplinaListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
                case 0: return QString("Denumire");
                case 1: return QString("Nr Ore");
                case 2: return QString("Tip");
                case 3: return QString("Profesor");

            }
            return QString("col %1").arg(section);
        }
        else {
            return QString("%1").arg(section);
        }
    }
    return QVariant();
}

void DisciplinaListModel::setList(const vector<Disciplina>& _disciplinaLIst)
{
    this->disciplinaList = _disciplinaLIst;
    const QModelIndex topLeft = createIndex(0, 0);
    const QModelIndex bottomRight = createIndex(rowCount(), columnCount());
    dataChanged(topLeft, bottomRight);
    layoutChanged();
}