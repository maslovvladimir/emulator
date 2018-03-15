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

#ifndef CALLIBRI_DEVICE_H
#define CALLIBRI_DEVICE_H

#include "device_processor.h"
#include "core_device.h"
#include "callibri_module_container.h"

namespace Nes
{

class CallibriDevice : public CoreDevice {
public:
    CallibriDevice(std::shared_ptr<CallibriModuleList>) noexcept;
    CallibriDevice(const CallibriDevice &) = delete;
    CallibriDevice& operator=(const CallibriDevice &) = delete;
    virtual ~CallibriDevice() noexcept = default;

private:
    const std::shared_ptr<CallibriModuleList> moduleContainer;
    DeviceProcessor deviceProcessor;

    void onCommandReceived(const ByteBuffer &) noexcept override;
    void processCommand(const ByteBuffer &) noexcept;
    void doWork() noexcept;
    void sendResponse() noexcept;
};

}

#endif // CALLIBRI_DEVICE_H
