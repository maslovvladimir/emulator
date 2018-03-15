#include "brainbit_impl.h"


BrainbitImpl::BrainbitImpl()
    //devicePtr(new Nes::BrainbitDevice()),
    //bleDevice(std::make_shared<Nes::BleDevice>(devicePtr))
{

}

void BrainbitImpl::setName(QString name){
}

QString BrainbitImpl::getName() const {
    return QString("Brainbit");
}

void BrainbitImpl::setAddress(QString address){

}

QString BrainbitImpl::getAddress() const {
    return QString("00:22:44:11:33:55");
}

DeviceType BrainbitImpl::getType() const {
    return DeviceType::Brainbit;
}

void BrainbitImpl::setEnabled(bool is_enabled){
    enabled = is_enabled;
}

bool BrainbitImpl::isEnabled() const {
    return enabled;
}

bool BrainbitImpl::hasModules() const {
    return false;
}

QString BrainbitImpl::getColor() const {
    return QString("#666666");
}

void BrainbitImpl::activate(){
}

std::weak_ptr<Nes::ServerDeviceInterface> BrainbitImpl::getBleDevice() const {
    return std::shared_ptr<Nes::ServerDeviceInterface>();
}
