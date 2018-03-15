#ifndef DEVICELISTMODEL_H
#define DEVICELISTMODEL_H

#include <QAbstractListModel>
#include <memory>
#include <vector>

class DeviceList;

class DeviceListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(DeviceList *list READ getDevList WRITE setDevList)
public:
    explicit DeviceListModel(QObject *parent = nullptr);

    enum {
        DeviceNameRole = Qt::UserRole,
        DeviceAddressRole = Qt::UserRole + 1,
        DeviceEnabledRole = Qt::UserRole + 2,
        ColorRole = Qt::UserRole + 3,
        HasModulesRole = Qt::UserRole + 4,
        SelectedTypeIndexRole = Qt::UserRole + 5
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    virtual QHash<int, QByteArray> roleNames() const override;

    DeviceList *getDevList() const;
    void setDevList(DeviceList *value);

private:
    DeviceList *devList;
};

#endif // DEVICELISTMODEL_H
