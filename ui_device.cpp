#include <cassert>
#include "ui_device.h"
#include "ui_device_impl.h"

UiDevice::UiDevice(std::unique_ptr<UiDeviceImpl> implementation):
    impl(std::move(implementation)){
    assert(impl);
}

UiDevice::~UiDevice(){}

void UiDevice::setName(QString name){
    assert(impl);
    impl->setName(name);
}

QString UiDevice::getName() const {
    assert(impl);
    return impl->getName();
}

void UiDevice::setAddress(QString address) {
    assert(impl);
    impl->setAddress(address);
}

QString UiDevice::getAddress() const {
    assert(impl);
    return impl->getAddress();
}

void UiDevice::setImpl(std::unique_ptr<UiDeviceImpl> implementation){
    assert(impl);
    if (impl->getType() != implementation->getType()){
        impl.reset(implementation.release());
    }
}

DeviceType UiDevice::getType() const {
    assert(impl);
    return impl->getType();
}

void UiDevice::setEnabled(bool enabled){
    assert(impl);
    impl->setEnabled(enabled);
}

bool UiDevice::isEnabled() const {
    assert(impl);
    return impl->isEnabled();
}

bool UiDevice::hasModules() const {
    assert(impl);
    return impl->hasModules();
}

QString UiDevice::getColor() const {
    assert(impl);
    return impl->getColor();
}

void UiDevice::activate(){
    assert(impl);
    impl->activate();
}

std::weak_ptr<Nes::ServerDeviceInterface> UiDevice::getBleDevice() const {
    assert(impl);
    return impl->getBleDevice();
}
