#include <cassert>
#include <iostream>
#include "emulation_server.h"
#include "socket.h"
#include "device_client.h"

namespace Nes
{

EmulationServer::EmulationServer(ServerDeviceContainer<UiDevice> *devices):
    deviceList(devices), serverSocket(27001){

    assert(deviceList!=nullptr);

    serverSocket.setClientConnectedCallback([=](std::unique_ptr<Net::TcpClientSocket> client){
        auto sharedClient = std::shared_ptr<Net::TcpClientSocket>(client.release());
        std::weak_ptr<Net::TcpClientSocket> weakClient = sharedClient;
        clientList.push_back(sharedClient);
        sharedClient->setDisconnectedCallback([=](){
            auto cl = weakClient.lock();
            if (!cl) return;
            for (auto shCl = clientList.begin(); shCl!=clientList.end(); ++shCl){
                if (*shCl == cl){
                    //clientList.erase(shCl);
                    break;
                }
            }
        });
        sharedClient->setDataReceivedCallback([=](ByteBuffer data){
            onDeviceRequest(weakClient, data);
        });
        onConnectRequest(weakClient);
    });
    serverSocket.startListen();
}

EmulationServer::~EmulationServer(){
    Net::sockets_cleanup();
}

void EmulationServer::onDeviceRequest(std::weak_ptr<Net::TcpClientSocket> client, const Net::ByteBuffer &data){
    auto cl = client.lock();
    if (!cl) return;
    if (data.size()<10){
        assert(false);
        return;
    }
    auto requestString = Net::convert_to_string(data);
    if (requestString.compare(0, 1, std::string("[")) == 0)    {
        //connect request
        auto loc = requestString.find("]", 1);
        if (loc != std::string::npos){
            std::string address;
            address.assign(requestString, 1, loc-1);
            auto device = getDeviceByAddress(address);
            if (device){
                std::string portStr;
                portStr.assign(requestString, loc+1, 5);
                auto port = std::stoi(portStr);
                try{
                    std::unique_ptr<DeviceClient> devClient(new DeviceClient(port, device->port()));
                    device->connect(std::move(devClient));
                    cl->send(Net::to_byte_buffer(std::to_string(device->port())));
                }
                catch (std::runtime_error &e){
                    std::cerr<< "Failed to create device connection: " << e.what() << std::endl;
                    assert(false && e.what());
                }
            }
            else {
                cl->send(Net::to_byte_buffer(std::string("CANCEL")));
            }
        }
    }
    else if (requestString.compare(0, 1, std::string("{")) == 0){
        //disconnect request
        auto loc = requestString.find("}", 1);
        if (loc != std::string::npos){
            std::string address;
            address.assign(requestString, 1, loc-1);
            auto device = getDeviceByAddress(address);
            if (device){
                device->disconnect();
            }
            try{
                cl->send(Net::to_byte_buffer(std::string("OK")));
            }
            catch (std::runtime_error &e){
                std::cerr<< "Failed to send disconnect response: " <<e.what()<<std::endl;
                assert(false);
            }

        }
    }
}

void EmulationServer::onConnectRequest(const std::weak_ptr<Net::TcpClientSocket> &client){
    auto devices = getDeviceList();
    auto devString = covertListToString(devices);
    auto cl = client.lock();
    if (!cl) return;
    try{
        cl->send(Net::to_byte_buffer(devString));
    }
    catch (std::runtime_error &e){
        std::cerr<< "Failed to send connect response: " <<e.what()<<std::endl;
        assert(false);
    }
}

std::vector<std::weak_ptr<ServerDeviceInterface> > EmulationServer::getDeviceList(){
    std::vector<std::weak_ptr<ServerDeviceInterface>> bleDevices;
    for (auto devPtr : *deviceList){
        if (!devPtr || !devPtr->isEnabled()) continue;
        bleDevices.push_back(devPtr->getBleDevice());
    }
    return bleDevices;
}

std::string EmulationServer::covertListToString(std::vector<std::weak_ptr<ServerDeviceInterface>> devices){
    std::string listString;
    for (auto devPtr : devices){
        auto dev = devPtr.lock();
        if (!dev) continue;
        listString += std::string("<") + dev->getName() + std::string("|")+dev->getAddress()+std::string(">");
    }
    return listString;
}

std::shared_ptr<ServerDeviceInterface> EmulationServer::getDeviceByAddress(std::string address){
    for (auto devPtr : *deviceList){
        auto dev = devPtr->getBleDevice().lock();
        if (!dev) continue;
        if (dev->getAddress() == address){
            return dev;
        }
    }
    return std::shared_ptr<ServerDeviceInterface>();
}

}
