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

#ifndef DEVICE_CLIENT_H
#define DEVICE_CLIENT_H

#include <memory>
#include "nes_types.h"
#include "socket.h"

namespace Nes
{

class DeviceClient{
private:
    class Impl;
    std::unique_ptr<Impl> impl;

public:
    class EventCallback{
    public:
        EventCallback() = default;
        EventCallback(const EventCallback &) = delete;
        EventCallback& operator=(const EventCallback &) = delete;
        virtual ~EventCallback() noexcept  = default;

    private:
        friend class Impl;
        virtual void onCommandReceived(const ByteBuffer &) noexcept = 0;
    };

    using EventCallbackPtr = std::weak_ptr<EventCallback>;

    DeviceClient(Net::PortNumberType remote_port, Net::PortNumberType this_port);
    DeviceClient(const DeviceClient &) = delete;
    DeviceClient& operator=(const DeviceClient &) = delete;
    ~DeviceClient();

    void setEventCallback(EventCallbackPtr) noexcept;
    bool send(const ByteBuffer &) noexcept;
};

}

#endif // DEVICE_CLIENT_H
