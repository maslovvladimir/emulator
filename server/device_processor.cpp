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

#include <atomic>
#include <cassert>
#include <condition_variable>
#include <mutex>
#include <system_error>
#include <thread>
#include <vector>
#include "device_processor.h"

namespace Nes
{

class DeviceProcessor::Impl{
private:
    using CommandContainer = std::vector<ByteBuffer>;

    const ProcessCommandCallable processCommand;
    const DoWorkCallable doWork;
    const SendResponseCallable sendResponse;    
    std::atomic<bool> deviceLoopStop{false};
    CommandContainer receivedCommands;
    std::mutex receivedCommandsMutex;
    std::thread deviceLoopThread;

    CommandContainer popAllCommands(){
        std::unique_lock<std::mutex> receivedCommandsLock(receivedCommandsMutex);
        CommandContainer tempCommandContainer;
        using std::swap;
        swap(receivedCommands, tempCommandContainer);
        return tempCommandContainer;
    }

    void deviceLoopFunc() noexcept {
        while(!deviceLoopStop.load()){
            auto commands = popAllCommands();
            if (deviceLoopStop.load()) return;

            for (auto& cmd : commands){
                processCommand(cmd);
                if (deviceLoopStop.load()) return;
            }

            if (deviceLoopStop.load()) return;
            doWork();

            if (deviceLoopStop.load()) return;
            sendResponse();

            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }

    void stopDeviceLoop() noexcept {
        if(!deviceLoopThread.joinable()){
            assert(false);
            return;
        }

        deviceLoopStop.store(true);

        try{
            deviceLoopThread.join();
        }
        catch (const std::system_error& error){
            notify_error_occured(error.code(), error.what());
            assert(false);
        }
    }

public:
    Impl(ProcessCommandCallable procCmdClb, DoWorkCallable doWorkClb, SendResponseCallable sendRespClb):
        processCommand(procCmdClb),
        doWork(doWorkClb),
        sendResponse(sendRespClb),
        deviceLoopThread(&Impl::deviceLoopFunc, this){

        assert(processCommand);
        assert(doWork);
        assert(sendResponse);
        assert(deviceLoopThread.joinable());
    }

    ~Impl() noexcept {
        stopDeviceLoop();
    }

    void pushCommand(const ByteBuffer &command_packet){
        std::unique_lock<std::mutex> receivedCommandsLock(receivedCommandsMutex);
        receivedCommands.push_back(command_packet);
    }
};

DeviceProcessor::DeviceProcessor(ProcessCommandCallable procCmdClb,
                                 DoWorkCallable doWorkClb,
                                 SendResponseCallable sendRespClb):impl(new Impl(procCmdClb, doWorkClb, sendRespClb)){}
DeviceProcessor::~DeviceProcessor(){}
void DeviceProcessor::pushCommand(const ByteBuffer &command_packet){ impl->pushCommand(command_packet); }

}
