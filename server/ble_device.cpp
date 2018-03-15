/*
 * Copyright 2016 - 2018 Neurotech MRC. http://neurotech.ru/
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <cassert>
#include "core_device.h"
#include "ble_device.h"

namespace Nes
{

class BleDevice::Impl{
private:
    std::string name{"Default_Neuro_Device"};
    std::string address{"11:22:33:44::55::66"};
    DeviceState state{DeviceState::DISABLED};
    std::shared_ptr<CoreDevice> coreDevice;
    unsigned short mPort;

public:
    Impl(std::shared_ptr<CoreDevice> core_device) noexcept : coreDevice(core_device){
        assert(coreDevice != nullptr);
        static unsigned short initPort = 37001;
        mPort = initPort++;

    }

    void setName(std::string name) noexcept {
        this->name = name;
    }

    void setAddress(std::string address) noexcept {
        this->address = address;
    }

    void enable() noexcept {
        if (state != DeviceState::DISABLED)
            return;

        state = DeviceState::ENABLED;
    }

    void disable() noexcept {
        state = DeviceState::DISABLED;
    }

    void connect(std::unique_ptr<DeviceClient> client) noexcept {
        if (state != DeviceState::ENABLED)
            return;

        coreDevice->setDeviceClient(std::move(client));
        state = DeviceState::CONNECTED;
    }

    void disconnect() noexcept {
        if (state != DeviceState::CONNECTED)
            return;

        coreDevice->setDeviceClient(nullptr);
        state = DeviceState::ENABLED;
    }

    std::string getName() const noexcept {
        return name;
    }

    std::string getAddress() const noexcept {
        return address;
    }

    DeviceState getState() const noexcept {
        return state;
    }

    unsigned short port() const noexcept{
        return mPort;
    }
};

BleDevice::BleDevice(std::shared_ptr<CoreDevice> core_device) noexcept : impl(new Impl(core_device)){}
BleDevice::~BleDevice() noexcept {}
void BleDevice::setName(std::string name) noexcept { impl->setName(name); }
void BleDevice::setAddress(std::string address) noexcept { impl->setAddress(address); }
void BleDevice::enable() noexcept { impl->enable(); }
void BleDevice::disable() noexcept { impl->disable(); }
void BleDevice::connect(std::unique_ptr<DeviceClient> client) noexcept { impl->connect(std::move(client)); }
void BleDevice::disconnect() noexcept { impl->disconnect(); }
std::string BleDevice::getName() const noexcept { return impl->getName(); }
std::string BleDevice::getAddress() const noexcept { return impl->getAddress(); }
DeviceState BleDevice::getState() const noexcept { return impl->getState(); }
unsigned short BleDevice::port() const noexcept { return impl->port(); }

}

