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

#ifndef CORE_DEVICE_H
#define CORE_DEVICE_H

#include <memory>
#include "nes_types.h"
#include "device_client.h"

namespace Nes
{

class CoreDevice : public DeviceClient::EventCallback, public std::enable_shared_from_this<CoreDevice>{
    /*pImpl*/
private:
    class Impl;
    std::unique_ptr<Impl> impl;
public:
    CoreDevice() noexcept;
    CoreDevice(const CoreDevice &) = delete;
    CoreDevice& operator=(const CoreDevice &) = delete;
    virtual ~CoreDevice() noexcept;

    void setDeviceClient(std::unique_ptr<DeviceClient>) noexcept;
protected:
    void sendToClient(const ByteBuffer &) noexcept;
};

}

#endif // CORE_DEVICE_H
