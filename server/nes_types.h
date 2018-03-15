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

#ifndef DEVICE_STATE_H
#define DEVICE_STATE_H

#include <string>
#include <vector>
#include "net_types.h"

#define NOT_IMPLEMENTED static_assert(false, "Function is not implemented")
#define NOOP(VAR) static_cast<void>(VAR)

namespace Nes
{

using Net::Byte;
using Net::ByteBuffer;

enum class OS { WIN, POSIX };

constexpr OS build_sys(){
#if defined(__linux__) || defined(__ANDROID) || defined(__APPLE__)
    return OS::POSIX;
#elif defined(_WIN64) || defined (_WIN32)
    return OS::WIN;
#else
    static_assert(false, "Unsupported platform");
#endif
}

#ifndef NDEBUG

template<typename T>
class TypeDeduction;

template<typename T>
constexpr void show_type(){
    TypeDeduction<T> var;
    NOOP(var);
}

#endif

template <typename CodeType>
inline void notify_error_occured(CodeType code, std::string what){
   //NOT_IMPLEMENTED;
    NOOP(code);
    NOOP(what);
}

enum class DeviceState {
    ENABLED,
    DISABLED,
    CONNECTED
};

}
#endif // DEVICE_STATE_H
