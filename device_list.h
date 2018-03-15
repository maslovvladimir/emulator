#ifndef DEVICE_LIST_H
#define DEVICE_LIST_H

#include <QObject>
#include "ui_device.h"
#include "server/server_device_interface.h"
#include "property_page_model.h"
#include "callibri_common_model.h"
#include "callibri_signal_model.h"

class DeviceList : public QObject, public Nes::ServerDeviceContainer<UiDevice> {
    Q_OBJECT
public:
    using ContainerType = std::vector<std::shared_ptr<UiDevice>>;
    using iterator = typename ContainerType::iterator;

    explicit DeviceList(PropertyPageModel *, CallibriCommonModel *, CallibriSignalModel*, QObject *parent);
    std::weak_ptr<UiDevice> operator[](int);
    iterator begin() override;
    iterator end() override;
    int size();
    std::unique_ptr<UiDeviceImpl> getImpl(DeviceType);
signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();

public slots:
    void appendItem();
    void removeItem(int index);
    void selectItem(int index, int module = 0);

private:
    PropertyPageModel * const pageModel;
    CallibriCommonModel * const callibriCommonModel;    
    CallibriSignalModel * const callibriSignalModel;
    ContainerType deviceItems;
};

#endif // DEVICE_LIST_H
