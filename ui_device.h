#ifndef UI_DEVICE_H
#define UI_DEVICE_H

#include <memory>
#include <QString>
#include "device_type.h"
#include "ui_device_impl.h"

class UiDevice{
public:
    UiDevice(std::unique_ptr<UiDeviceImpl>);
    ~UiDevice();

    void setName(QString name);
    QString getName() const;
    void setAddress(QString address);
    QString getAddress() const;
    void setImpl(std::unique_ptr<UiDeviceImpl>);
    DeviceType getType() const;
    void setEnabled(bool);
    bool isEnabled() const;
    bool hasModules() const;
    QString getColor() const;
    void activate();
    std::weak_ptr<Nes::ServerDeviceInterface> getBleDevice() const;

private:
    std::unique_ptr<UiDeviceImpl> impl;
};

#endif // UI_DEVICE_H
