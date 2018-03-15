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

#ifndef EMULATION_SERVER_H
#define EMULATION_SERVER_H

#include <atomic>
#include <thread>
#include "ui_device.h"
#include "server_device_interface.h"
#include "socket.h"

namespace Nes
{

class EmulationServer final {
public:
    EmulationServer(ServerDeviceContainer<UiDevice> *);
    EmulationServer(const EmulationServer &) = delete;
    EmulationServer& operator=(const EmulationServer &) = delete;
    ~EmulationServer();

private:
    ServerDeviceContainer<UiDevice> *deviceList;
    std::vector<std::shared_ptr<Net::TcpClientSocket>> clientList;
    Net::TcpServerSocket serverSocket;
    std::atomic<bool> isWorking{true};
    std::thread serverThread;

    void onConnectRequest(const std::weak_ptr<Net::TcpClientSocket> &);
    void onDeviceRequest(std::weak_ptr<Net::TcpClientSocket>, const ByteBuffer &);
    std::vector<std::weak_ptr<ServerDeviceInterface>> getDeviceList();
    std::string covertListToString(std::vector<std::weak_ptr<ServerDeviceInterface>>);
    std::shared_ptr<ServerDeviceInterface> getDeviceByAddress(std::string);
};

}

#endif //EMULATION_SERVER_H
