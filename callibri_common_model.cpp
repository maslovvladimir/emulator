#include "callibri_common_model.h"
//#include "saturation_cast.h"

CallibriCommonModel::CallibriCommonModel(QObject *parent) : QObject(parent) {

}

void CallibriCommonModel::setModule(std::weak_ptr<Nes::CallibriMainModule> common_module){
    modulePtr = common_module;
    auto module = modulePtr.lock();
    if (module){
        module->setSwitchStateCallback([=](){ emit extSwitchIndexChanged(); });
    }
    emitAll();
}

int CallibriCommonModel::address() const noexcept {
    auto module = modulePtr.lock();
    if (!module)
        return 0;

    return module->getAddress();
}

int CallibriCommonModel::firmware() const noexcept {
    auto module = modulePtr.lock();
    if (!module)
        return 0;

    return module->getFirmwareVersion();
}

int CallibriCommonModel::build() const noexcept {
    auto module = modulePtr.lock();
    if (!module)
        return 0;

    return module->getBuildVersion();
}

int CallibriCommonModel::radioFreq() const noexcept {
    return 0;
}

int CallibriCommonModel::extSwitchIndex() const noexcept {
    auto module = modulePtr.lock();
    if (!module)
        return 0;

    return static_cast<int>(module->getExtSwitchState());
}

int CallibriCommonModel::batteryVoltage() const noexcept {
    auto module = modulePtr.lock();
    if (!module)
        return 0;

    return module->getBatteryVoltageMv();
}

void CallibriCommonModel::setAddress(int address){
    auto module = modulePtr.lock();
    if (!module)
        return;

    module->setAddress(address);
    emit addressChanged();
}

void CallibriCommonModel::setFirmware(int firmware){
    auto module = modulePtr.lock();
    if (!module)
        return;

    module->setFirmwareVersion(/*saturation_cast<unsigned short>*/(firmware));
    emit firmwareChanged();
}

void CallibriCommonModel::setBuild(int build){
    auto module = modulePtr.lock();
    if (!module)
        return;

    module->setBuildVersion(build);
    emit buildChanged();
}

void CallibriCommonModel::setRadioFreq(int){
    //do nothing
}

void CallibriCommonModel::setExtSwitchIndex(int state){
    auto module = modulePtr.lock();
    if (!module)
        return;

    module->setExtSwitchState(static_cast<Nes::ExtSwitchState>(state));
    //no emit here, callback passed
}

void CallibriCommonModel::setBatteryVoltage(int voltage){
    auto module = modulePtr.lock();
    if (!module)
        return;

    module->setBatteryVoltageMv(voltage);
    emit batteryVoltageChanged();
}

void CallibriCommonModel::emitAll(){
    emit addressChanged();
    emit firmwareChanged();
    emit buildChanged();
    emit radioFreqChanged();
    emit extSwitchIndexChanged();
    emit batteryVoltageChanged();
}


