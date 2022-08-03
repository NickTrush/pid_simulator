#include "include/pid_table_model.h"

PidTableModel::PidTableModel(QObject *parent):
    QAbstractTableModel(parent),
    targetCoordinate(0),
    pidCoefficients {0, 0, 0}
{
}

int PidTableModel::rowCount(const QModelIndex& index) const
{
    Q_UNUSED(index)
    return static_cast<int>(vertical_headers.size());
}

int PidTableModel::columnCount(const QModelIndex& index) const
{
    Q_UNUSED(index)
    return static_cast<int>(horizontal_headers.size());
}

QVariant PidTableModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (index.row() == 0)
            return targetCoordinate;

        return pidCoefficients.at(index.row() - 1);
    }

    return QVariant();
}

QVariant PidTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        switch(orientation)
        {
            case(Qt::Horizontal):
            {
                return horizontal_headers.at(section);
            }
            case(Qt::Vertical):
            {
                return vertical_headers.at(section);
            }
        }
    }

    return QVariant();
}

Qt::ItemFlags PidTableModel::flags(const QModelIndex& index) const
{
    Q_UNUSED(index)
    return Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

bool PidTableModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (role == Qt::EditRole && value.canConvert<float>())
    {
        if (index.row() == 0) targetCoordinate = value.toReal();
        else pidCoefficients[index.row() - 1] = static_cast<float>(value.toReal());

        return true;
    }

    return false;
}

qreal PidTableModel::getTargetCoordinate() const
{
    return targetCoordinate;
}

QVector<float> PidTableModel::getPidCoefficients() const
{
    return pidCoefficients;
}

