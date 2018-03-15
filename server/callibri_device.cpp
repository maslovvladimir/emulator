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

#include <functional>
#include <memory>
#include "callibri_device.h"
#include "callibri_module_container.h"
#include "device_processor.h"

namespace Nes
{

CallibriDevice::CallibriDevice(std::shared_ptr<CallibriModuleList> modules) noexcept : moduleContainer(modules),
    deviceProcessor([this](const ByteBuffer &cmd){return processCommand(cmd);},
                       [this](){return doWork();},
                       [this](){return sendResponse();}
                       ){}

void CallibriDevice::onCommandReceived(const ByteBuffer &command_packet) noexcept {
    deviceProcessor.pushCommand(command_packet);
}

void CallibriDevice::processCommand(const ByteBuffer &command_packet) noexcept {
    if (moduleContainer->size() == 0) return;

    auto firstResponsible = moduleContainer->back();
    firstResponsible->processCommand(command_packet);
}

void CallibriDevice::doWork() noexcept {
    for (auto& module : *moduleContainer){
        module->doWork();
    }
}

void CallibriDevice::sendResponse() noexcept {
    for (auto& module : *moduleContainer){
        auto responsePackets = module->readData();
        for (auto& packet : responsePackets){
            sendToClient(packet);
        }
    }
}

}
