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

namespace Nes
{

class CoreDevice::Impl{
private:
    std::unique_ptr<DeviceClient> deviceClient{nullptr};

public:
    void setDeviceClient(std::unique_ptr<DeviceClient> client) noexcept {
        deviceClient.reset(client.release());
    }

    void sendToClient(const ByteBuffer &data) noexcept {
        if (!deviceClient)
            return;

        auto sendResult = deviceClient->send(data);
        assert(sendResult);
    }
};

CoreDevice::CoreDevice() noexcept : impl(new Impl()){}
CoreDevice::~CoreDevice() noexcept {}
void CoreDevice::sendToClient(const ByteBuffer &data) noexcept { impl->sendToClient(data); }

void CoreDevice::setDeviceClient(std::unique_ptr<DeviceClient> client) noexcept {
    if (client) client->setEventCallback(shared_from_this());
    impl->setDeviceClient(std::move(client));
}

}
