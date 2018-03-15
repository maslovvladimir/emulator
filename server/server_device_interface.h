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

#ifndef SERVER_DEVICE_INTERFACE_H
#define SERVER_DEVICE_INTERFACE_H

#include <memory>
#include <string>
#include <vector>
#include <iterator>
#include "nes_types.h"

namespace Nes
{

class DeviceClient;

class ServerDeviceInterface{
public:
    ServerDeviceInterface() noexcept = default;
    ServerDeviceInterface(const ServerDeviceInterface &) = delete;
    ServerDeviceInterface& operator=(const ServerDeviceInterface &) = delete;
    virtual ~ServerDeviceInterface() = default;

    virtual void connect(std::unique_ptr<DeviceClient>) noexcept = 0;
    virtual void disconnect() noexcept = 0;

    virtual std::string getName() const noexcept = 0;
    virtual std::string getAddress() const noexcept = 0;
    virtual DeviceState getState() const noexcept = 0;
    virtual unsigned short port() const noexcept = 0;
};

template <typename T>
class ServerDeviceContainer{
public:
    virtual ~ServerDeviceContainer() = default;

    using iterator = typename std::vector<std::shared_ptr<T>>::iterator;

    virtual iterator begin() = 0;
    virtual iterator end() = 0;
};

}

#endif // SERVER_DEVICE_INTERFACE_H
