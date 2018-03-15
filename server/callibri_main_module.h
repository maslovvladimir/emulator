#ifndef CALLIBRI_MAIN_MODULE_H
#define CALLIBRI_MAIN_MODULE_H

#include "callibri_generic_module.h"
#include "nes_types.h"

namespace Nes
{

using CallibriMainBaseModule = CallibriGenericModule<
CallibriCommandCode::ECHO,
CallibriCommandCode::GET_ADDR,
CallibriCommandCode::GET_AKK_VOLTAGE,
CallibriCommandCode::GET_SENSOR_PARAM,
CallibriCommandCode::BOOT_ACTIVATE_APP,
CallibriCommandCode::SWITCH_EXT_COM_INPUTS>;

class CallibriMainModule : public CallibriMainBaseModule {
public:
    CallibriMainModule(std::shared_ptr<CallibriCommonParameters>) noexcept;
    ~CallibriMainModule() = default;

    unsigned short getBatteryVoltageMv() const noexcept;
    void setBatteryVoltageMv(unsigned short) noexcept;
    CallibriAddressType getAddress() const noexcept;
    void setAddress(CallibriAddressType) noexcept;
    unsigned char getFirmwareVersion() const noexcept;
    void setFirmwareVersion(unsigned char) noexcept;
    unsigned short getBuildVersion() const noexcept;
    void setBuildVersion(unsigned short) noexcept;
    ExtSwitchState getExtSwitchState() const noexcept;
    void setExtSwitchState(ExtSwitchState) noexcept;
    void setSwitchStateCallback(std::function<void(void)>);

private:
    CallibriAddressType address{0xAABBCC};
    unsigned char firmwareVersion{0xB0};
    unsigned short buildVersion{8800};
    unsigned short batteryVoltageMv{4700};
    CallibriMode mode{CallibriMode::APPLICATION};

    void doWork() noexcept override;
    void handleCommand(const CallibriCommand &) noexcept override;
    void onEchoCommand() noexcept;
    void onGetAddrCommand() noexcept;
    void onGetAkkVoltageCommand() noexcept;
    void onGetSensorParamsCommand() noexcept;
    void onBootActivateAppCommand() noexcept;
    void onSwitchExtComInputs(CallibriCommand) noexcept;
    void onUnknowCommand() noexcept;
};

}

#endif // CALLIBRI_MAIN_MODULE_H
