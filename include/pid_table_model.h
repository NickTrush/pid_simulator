#ifndef PIDTABLE_H
#define PIDTABLE_H

#include <QAbstractTableModel>
#include <QDebug>

class PidTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    PidTableModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

    qreal getTargetCoordinate() const;
    QVector<float> getPidCoefficients() const;

private:
    qreal targetCoordinate;
    QVector<float> pidCoefficients;
    const QStringList horizontal_headers = {"Y"};
    const QStringList vertical_headers = {
        "Пункт назначения",
        "Kp",
        "Ki",
        "Kd"};
};

#endif
