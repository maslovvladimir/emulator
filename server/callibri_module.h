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

#ifndef CALLIBRI_MODULE_H
#define CALLIBRI_MODULE_H

#include <memory>
#include <vector>
#include "nes_types.h"

namespace Nes
{

template <template <typename...> class T>
class CallibriModuleContainer;

class CallibriCommand;

class CallibriModule{
public:
    CallibriModule() noexcept;
    CallibriModule(const CallibriModule &) = delete;
    CallibriModule& operator=(const CallibriModule &) = delete;
    virtual ~CallibriModule() = default;

    void processCommand(const ByteBuffer &) noexcept;
    virtual void doWork() noexcept = 0;
    std::vector<ByteBuffer> readData() noexcept;

protected:
    void pushResponse(const CallibriCommand &) noexcept;

private:
    template <template <typename...> class T>
    friend class CallibriModuleContainer;

    std::weak_ptr<CallibriModule> successorModule;
    std::vector<ByteBuffer> pendingResponses;

    void setSuccessor(std::weak_ptr<CallibriModule>) noexcept;
    virtual bool checkIfResponsible(const CallibriCommand &) noexcept = 0;
    virtual void handleCommand(const CallibriCommand &) noexcept = 0;
    void passToSuccessor(const ByteBuffer &) noexcept;
    void sendNoCommandError() noexcept;
};

}

#endif // CALLIBRI_MODULE_H
