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

#ifndef DEVICE_PROCESSOR_H
#define DEVICE_PROCESSOR_H

#include <functional>
#include <memory>
#include "nes_types.h"

namespace Nes
{

class DeviceProcessor{
    /*pImpl*/
private:
    class Impl;
    std::unique_ptr<Impl> impl;

public:
    using ProcessCommandCallable = std::function<void(const ByteBuffer &)>;
    using DoWorkCallable = std::function<void()>;
    using SendResponseCallable = std::function<void()>;

    DeviceProcessor(ProcessCommandCallable, DoWorkCallable, SendResponseCallable);
    DeviceProcessor(const DeviceProcessor &) = delete;
    DeviceProcessor& operator=(const DeviceProcessor &) = delete;
    ~DeviceProcessor();

    void pushCommand(const ByteBuffer &);
};

}
#endif // DEVICE_PROCESSOR_H
