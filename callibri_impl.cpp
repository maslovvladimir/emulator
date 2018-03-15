#include "callibri_impl.h"
#include <random>

CallibriImpl::CallibriImpl(CallibriCommonModel *common_model, CallibriSignalModel *signal_model):
    sineGenerator(new SineGenerator()),
    commonParams(new Nes::CallibriCommonParameters()),
    mainModule(new Nes::CallibriMainModule(commonParams)),
    signalModule(new Nes::CallibriSignalModule(commonParams, sineGenerator)),
    moduleListPtr(new Nes::CallibriModuleList({mainModule, signalModule})),
    devicePtr(new Nes::CallibriDevice(moduleListPtr)),
    bleDevice(std::make_shared<Nes::BleDevice>(devicePtr)),
    commonModel(common_model),
    signalModel(signal_model){

    initializeDevice();
}

void CallibriImpl::setName(QString name){
    bleDevice->setName(name.toStdString());
}

QString CallibriImpl::getName() const {
    return QString::fromStdString(bleDevice->getName());
}

void CallibriImpl::setAddress(QString address){
    bleDevice->setAddress(address.toStdString());
}

QString CallibriImpl::getAddress() const {
    return QString::fromStdString(bleDevice->getAddress());
}

DeviceType CallibriImpl::getType() const {
    return DeviceType::Callibri;
}

void CallibriImpl::setEnabled(bool enable){
    enable ? bleDevice->enable() : bleDevice->disable();
}

bool CallibriImpl::isEnabled() const {
    auto state = bleDevice->getState();
    return state == Nes::DeviceState::ENABLED || state == Nes::DeviceState::CONNECTED;
}

bool CallibriImpl::hasModules() const {
    return true;
}

QString CallibriImpl::getColor() const {
    return parseNameToColor(QString::fromStdString(bleDevice->getName()));
}

void CallibriImpl::activate(){
    commonModel->setModule(mainModule);
    signalModel->setModule(signalModule);
    signalModel->setSineGenerator(sineGenerator);
}

std::weak_ptr<Nes::ServerDeviceInterface> CallibriImpl::getBleDevice() const {
    return bleDevice;
}

QString CallibriImpl::parseNameToColor(QString name) const noexcept{
    if (name.endsWith("_R")){
        return QString("#dd8888");
    }
    else if (name.endsWith("_B")){
        return QString("#8888dd");
    }
    else if (name.endsWith("_Y")){
        return QString("#dddd88");
    }
    else if (name.endsWith("_W")){
        return QString("#eeeeee");
    }
    return QString("#666666");
}

void CallibriImpl::initializeDevice(){

    bleDevice->setName(generateName().toStdString());
    bleDevice->setAddress(generateBleAddress().toStdString());
    mainModule->setAddress(generateAddress());
}

QString CallibriImpl::generateName(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 3);

    auto name = QString("Neurotech_Callibri_");
    switch(dis(gen)){
    case 0:
        name.append("R");
        break;
    case 1:
        name.append("B");
        break;
    case 2:
        name.append("Y");
        break;
    case 3:
        name.append("W");
        break;
    }

    return name;
}

QString CallibriImpl::generateBleAddress(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, std::numeric_limits<unsigned char>::max());

    auto address = QString("");
    address.append(QString::number(dis(gen), 16));
    address.append(":");
    address.append(QString::number(dis(gen), 16));
    address.append(":");
    address.append(QString::number(dis(gen), 16));
    address.append(":");
    address.append(QString::number(dis(gen), 16));
    address.append(":");
    address.append(QString::number(dis(gen), 16));
    address.append(":");
    address.append(QString::number(dis(gen), 16));

    return address;
}

Nes::CallibriAddressType CallibriImpl::generateAddress(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 0xFFFFFF);

    return dis(gen);
}
