#ifndef UI_DEVICE_IMPL_H
#define UI_DEVICE_IMPL_H

#include <memory>
#include <QString>
#include "device_type.h"
#include "server/server_device_interface.h"


class UiDeviceImpl{
public:
    UiDeviceImpl()=default;
    UiDeviceImpl(const UiDeviceImpl &) = delete;
    UiDeviceImpl& operator=(const UiDeviceImpl &) = delete;
    virtual ~UiDeviceImpl() = default;

    virtual void setName(QString name) = 0;
    virtual QString getName() const = 0;
    virtual void setAddress(QString address) = 0;
    virtual QString getAddress() const = 0;
    virtual DeviceType getType() const = 0;
    virtual void setEnabled(bool) = 0;
    virtual bool isEnabled() const = 0;
    virtual bool hasModules() const = 0;
    virtual QString getColor() const = 0;
    virtual void activate() = 0;
    virtual std::weak_ptr<Nes::ServerDeviceInterface> getBleDevice() const = 0;
};

#endif // UI_DEVICE_IMPL_H
