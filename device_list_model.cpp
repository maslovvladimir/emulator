#include "device_list_model.h"
#include "device_list.h"

DeviceListModel::DeviceListModel(QObject *parent)
    : QAbstractListModel(parent),
      devList(nullptr){}

int DeviceListModel::rowCount(const QModelIndex &parent) const {
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    if (!devList){
        return 0;
    }

    return devList->size();
}

QVariant DeviceListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    auto device = (*devList)[index.row()].lock();

    if (!device)
        return QVariant();

    switch(role){
    case DeviceNameRole:
    {
        return QVariant(device->getName());
    }
    case DeviceAddressRole:
    {
        return QVariant(device->getAddress());
    }
    case DeviceEnabledRole:
    {
        return QVariant(device->isEnabled());
    }
    case ColorRole:
    {
        return QVariant(device->getColor());
    }
    case HasModulesRole:
    {
        return QVariant(device->hasModules());
    }
    case SelectedTypeIndexRole:
    {
        return QVariant(static_cast<int>(device->getType()));
    }
    }
    return QVariant();
}

bool DeviceListModel::setData(const QModelIndex &index, const QVariant &value, int role){
    if(!devList)
        return false;
    auto device = devList->operator [](index.row()).lock();
    if (!device)
        return false;

    switch(role){
    case DeviceNameRole: {
        auto name = value.toString();
        if (name != device->getName()){
            device->setName(name);
            emit dataChanged(index, index, QVector<int>() << DeviceNameRole << ColorRole);
            return true;
        }
        break;
    }
    case DeviceAddressRole:
    {
        auto address = value.toString();
        if (address != device->getAddress())
        {
            device->setAddress(address);
            emit dataChanged(index, index, QVector<int>() << DeviceAddressRole);
            return true;
        }
        break;
    }
    case DeviceEnabledRole:
    {
        auto isEnabled = value.toBool();
        if(isEnabled!= device->isEnabled())
        {
            device->setEnabled(value.toBool());
            emit dataChanged(index, index, QVector<int>() << DeviceEnabledRole);
            return true;
        }
        break;
    }
    case SelectedTypeIndexRole:
    {
        auto type = static_cast<DeviceType>(value.toInt());
        if (type!=device->getType())
        {
            auto impl = devList->getImpl(type);
            device->setImpl(std::move(impl));
            emit dataChanged(index, index,
                             QVector<int>()
                             << SelectedTypeIndexRole
                             << DeviceEnabledRole
                             << DeviceNameRole
                             << ColorRole
                             << HasModulesRole
                             << DeviceAddressRole);
            return true;
        }
        break;
    }
    }
    return false;
}

Qt::ItemFlags DeviceListModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

bool DeviceListModel::insertRows(int row, int count, const QModelIndex &parent){
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endInsertRows();
    return true;
}

bool DeviceListModel::removeRows(int row, int count, const QModelIndex &parent){
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endRemoveRows();
    return true;
}

QHash<int, QByteArray> DeviceListModel::roleNames() const {
    QHash<int, QByteArray> names;
    names[DeviceNameRole] = "deviceName";
    names[DeviceAddressRole] = "deviceAddress";
    names[DeviceEnabledRole] = "deviceEnabled";
    names[ColorRole] = "color";
    names[HasModulesRole] = "hasModules";
    names[SelectedTypeIndexRole] = "selectedTypeIndex";
    return names;
}

DeviceList *DeviceListModel::getDevList() const {
    return devList;
}

void DeviceListModel::setDevList(DeviceList *value) {
    beginResetModel();

    if (devList)
        devList->disconnect(this);

    devList = value;

    if (devList){
        connect(devList, &DeviceList::preItemAppended, this, [=](){
            const auto index = devList->size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(devList, &DeviceList::postItemAppended, this, [=](){
            endInsertRows();
        });
        connect(devList, &DeviceList::preItemRemoved, this, [=](int index){
            beginRemoveRows(QModelIndex(), index, index);
        });
        connect(devList, &DeviceList::postItemRemoved, this, [=](){
            endRemoveRows();
        });
    }

    endResetModel();
}
