#ifndef CALLIBRI_IMPL_H
#define CALLIBRI_IMPL_H

#include <memory>
#include "ui_device_impl.h"
#include "callibri_common_model.h"
#include "callibri_signal_model.h"
#include "sine_generator.h"
#include "server/ble_device.h"
#include "server/callibri_device.h"
#include "server/callibri_module_container.h"

class CallibriImpl final : public UiDeviceImpl{
public:
    CallibriImpl(CallibriCommonModel *, CallibriSignalModel *);

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
    std::shared_ptr<SineGenerator> sineGenerator;
    std::shared_ptr<Nes::CallibriCommonParameters> commonParams;
    std::shared_ptr<Nes::CallibriMainModule> mainModule;
    std::shared_ptr<Nes::CallibriSignalModule> signalModule;
    std::shared_ptr<Nes::CallibriModuleList> moduleListPtr;
    std::shared_ptr<Nes::CallibriDevice> devicePtr;
    std::shared_ptr<Nes::BleDevice> bleDevice;
    CallibriCommonModel * const commonModel;
    CallibriSignalModel * const signalModel;

    QString parseNameToColor(QString) const noexcept;
    void initializeDevice();
    QString generateName();
    QString generateBleAddress();
    Nes::CallibriAddressType generateAddress();
};

#endif // CALLIBRI_IMPL_H
