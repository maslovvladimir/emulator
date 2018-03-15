#include "callibri_main_module.h"
#include "callibri_command.h"

namespace Nes
{

CallibriMainModule::CallibriMainModule(std::shared_ptr<CallibriCommonParameters> params) noexcept :
    CallibriMainBaseModule(params){}

unsigned short CallibriMainModule::getBatteryVoltageMv() const noexcept {
    return batteryVoltageMv;
}

void CallibriMainModule::setBatteryVoltageMv(unsigned short voltage) noexcept {
    batteryVoltageMv = voltage;
}

CallibriAddressType CallibriMainModule::getAddress() const noexcept {
    return address;
}

void CallibriMainModule::setAddress(CallibriAddressType addr) noexcept {
    address = addr;
}

unsigned char CallibriMainModule::getFirmwareVersion() const noexcept {
    return firmwareVersion;
}

void CallibriMainModule::setFirmwareVersion(unsigned char firmware_version) noexcept {
    firmwareVersion = (firmware_version & 0x3F);
}

unsigned short CallibriMainModule::getBuildVersion() const noexcept {
    return buildVersion;
}

void CallibriMainModule::setBuildVersion(unsigned short build_version) noexcept {
    buildVersion = build_version;
}

ExtSwitchState CallibriMainModule::getExtSwitchState() const noexcept {
    return commonParameters->getExtSwitchState();
}

void CallibriMainModule::setExtSwitchState(ExtSwitchState state) noexcept {
    commonParameters->setExtSwitchState(state);
}

void CallibriMainModule::setSwitchStateCallback(std::function<void()> callback){
    commonParameters->setSwitchStateCallback(callback);
}

void CallibriMainModule::doWork() noexcept {

}

void CallibriMainModule::handleCommand(const CallibriCommand &command) noexcept {

    switch (command.code()){
        case CallibriCommandCode::ECHO: {
            onEchoCommand();
            break;
        }
        case CallibriCommandCode::GET_ADDR: {
            onGetAddrCommand();
            break;
        }
        case CallibriCommandCode::GET_AKK_VOLTAGE: {
            onGetAkkVoltageCommand();
            break;
        }
        case CallibriCommandCode::GET_SENSOR_PARAM: {
            onGetSensorParamsCommand();
            break;
        }
        case CallibriCommandCode::BOOT_ACTIVATE_APP: {
            onBootActivateAppCommand();
            break;
        }
    case CallibriCommandCode::SWITCH_EXT_COM_INPUTS: {
            onSwitchExtComInputs(command);
        }
        default: {
            onUnknowCommand();
        }
    }
}

void CallibriMainModule::onEchoCommand() noexcept {
    CallibriCommand echoResponse(CallibriCommandCode::ECHO, CallibriErrorCode::NO_ERROR, 0xA5B6C7);

    auto firmwareByte = firmwareVersion;
    if (mode == CallibriMode::BOOTLOADER)
        firmwareByte |= 0x40;
     echoResponse.data()[0] = firmwareByte;

    ByteInterpreter<unsigned short> build;
    build.value = buildVersion;
    echoResponse.data()[1] = build.bytes[0];
    echoResponse.data()[2] = build.bytes[1];
    pushResponse(echoResponse);
}

void CallibriMainModule::onGetAddrCommand() noexcept {
    CallibriCommand getAddrResponse(CallibriCommandCode::GET_ADDR, CallibriErrorCode::NO_ERROR, 0xA5B6C7);
    ByteInterpreter<CallibriAddressType> addressBuffer;
    addressBuffer.value = address;
    getAddrResponse.data()[0] = addressBuffer.bytes[0];
    getAddrResponse.data()[1] = addressBuffer.bytes[1];
    getAddrResponse.data()[2] = addressBuffer.bytes[2];
    pushResponse(getAddrResponse);
}

void CallibriMainModule::onGetAkkVoltageCommand() noexcept {
    CallibriCommand getAkkVoltageResponse(CallibriCommandCode::GET_AKK_VOLTAGE, CallibriErrorCode::NO_ERROR, 0xA5B6C7);
    ByteInterpreter<unsigned short> akkVoltage;
    akkVoltage.value = batteryVoltageMv;
    getAkkVoltageResponse.data()[0] = akkVoltage.bytes[0];
    getAkkVoltageResponse.data()[1] = akkVoltage.bytes[1];
    pushResponse(getAkkVoltageResponse);
}

void CallibriMainModule::onGetSensorParamsCommand() noexcept {
    CallibriCommand getSensorParamsResponse(CallibriCommandCode::GET_SENSOR_PARAM, CallibriErrorCode::NO_ERROR, 0xA5B6C7);
    getSensorParamsResponse.data()[0] = commonParameters->getModuleFlags();
    getSensorParamsResponse.data()[1] = static_cast<Byte>(commonParameters->getSamplingFrequency());
    getSensorParamsResponse.data()[2] = static_cast<Byte>(commonParameters->getAdcInputState());
    getSensorParamsResponse.data()[3] = static_cast<Byte>(commonParameters->getHpfState());
    getSensorParamsResponse.data()[4] = static_cast<Byte>(commonParameters->getGain());
    getSensorParamsResponse.data()[5] = static_cast<Byte>(commonParameters->getOffset());
    getSensorParamsResponse.data()[6] = static_cast<Byte>(commonParameters->getExtSwitchState());
    getSensorParamsResponse.data()[7] = 0;
    getSensorParamsResponse.data()[8] = 0;
    getSensorParamsResponse.data()[9] = 0;
    pushResponse(getSensorParamsResponse);
}

void CallibriMainModule::onBootActivateAppCommand() noexcept {
    if (mode == CallibriMode::BOOTLOADER){
        mode = CallibriMode::APPLICATION;
        pushResponse(CallibriCommand(CallibriCommandCode::BOOT_ACTIVATE_APP, CallibriErrorCode::NO_ERROR, 0xA5B6C7));
    }
    else{
        pushResponse(CallibriCommand(CallibriCommandCode::ERR_CMD, CallibriErrorCode::ERR_NO_CMD, 0xA5B6C7));
    }
}

void CallibriMainModule::onSwitchExtComInputs(CallibriCommand request) noexcept {
    auto switchStateValue = request.data()[0];
    if (switchStateValue > 3){
        pushResponse(CallibriCommand(CallibriCommandCode::ERR_CMD, CallibriErrorCode::ERR_WRONG_PARAM, 0xA5B6C7));
        return;
    }
    commonParameters->setExtSwitchState(static_cast<ExtSwitchState>(switchStateValue));
    pushResponse(CallibriCommand(CallibriCommandCode::SWITCH_EXT_COM_INPUTS, CallibriErrorCode::NO_ERROR, 0xA5B6C7));
}

void CallibriMainModule::onUnknowCommand() noexcept {
    pushResponse(CallibriCommand(CallibriCommandCode::ERR_CMD, CallibriErrorCode::ERR_NO_CMD, 0xA5B6C7));
}

}
