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
#include <iostream>
#include "socket.h"
#include "device_client.h"


namespace Nes
{

class DeviceClient::Impl {
private:
    Net::PortNumberType sendPort;
    std::unique_ptr<Net::UdpSocket> clientSocket;
    EventCallbackPtr eventCallbackPtr;

public:
    Impl(Net::PortNumberType remote_port, Net::PortNumberType this_port) :
        sendPort(remote_port),
        clientSocket(new Net::UdpSocket(this_port)){
        assert(clientSocket);
        clientSocket->setDataReceivedCallback([=](ByteBuffer data, std::string, Net::PortNumberType){
            auto evenCallback = eventCallbackPtr.lock();
            if (!evenCallback) return;
            evenCallback->onCommandReceived(data);
        });
    }

    void setEventCallback(EventCallbackPtr ptr) noexcept {
        eventCallbackPtr = ptr;
    }

    bool send(const ByteBuffer &data) noexcept {
        try{
            return clientSocket->sendTo("localhost", sendPort, data);
        }
        catch (std::runtime_error &e){
            std::cerr<< "Failed to send device data: " <<e.what()<<std::endl;
            assert(false);
            return false;
        }
    }
};

DeviceClient::DeviceClient(Net::PortNumberType remote_port, Net::PortNumberType this_port):impl(new Impl(remote_port, this_port)){}
DeviceClient::~DeviceClient() {}
void DeviceClient::setEventCallback(EventCallbackPtr ptr) noexcept { impl->setEventCallback(ptr); }
bool DeviceClient::send(const ByteBuffer &data) noexcept { return impl->send(data); }

}
