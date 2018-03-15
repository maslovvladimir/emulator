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

#ifndef EMULATED_DEVICE_H
#define EMULATED_DEVICE_H

#include <memory>
#include "nes_types.h"
#include "server_device_interface.h"

namespace Nes
{

class CoreDevice;
class DeviceClient;

class BleDevice : public ServerDeviceInterface{
    /*pImpl*/
private:
    class Impl;
    std::unique_ptr<Impl> impl;

public:
    BleDevice(std::shared_ptr<CoreDevice>) noexcept;
    ~BleDevice() noexcept;
    void setName(std::string) noexcept;
    void setAddress(std::string) noexcept;
    void enable() noexcept;
    void disable() noexcept;

    void connect(std::unique_ptr<DeviceClient>) noexcept override;
    void disconnect() noexcept override;

    std::string getName() const noexcept override;
    std::string getAddress() const noexcept override;
    DeviceState getState() const noexcept override;
    unsigned short port() const noexcept override;
};

}

#endif //EMULATED_DEVICE_H
