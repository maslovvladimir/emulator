#ifndef BRAINBIT_IMPL_H
#define BRAINBIT_IMPL_H

#include "ui_device_impl.h"

class BrainbitImpl final : public UiDeviceImpl{
public:
    BrainbitImpl();

    void setName(QString name) override;
    QString getName() const override;
    void setAddress(QString address) override;
    QString getAddress() const override;
    DeviceType getType() const override;
    void setEnabled(bool) override;
    bool isEnabled() const override;
    bool hasModules() const override;
    QString getColor() const override;
    void activate() override;
    std::weak_ptr<Nes::ServerDeviceInterface> getBleDevice() const override;

private:
    bool enabled; //TODO remove
};

#endif // BRAINBIT_IMPL_H
