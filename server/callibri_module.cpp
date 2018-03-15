#include "callibri_module.h"
#include "callibri_command.h"

namespace Nes
{

CallibriModule::CallibriModule() noexcept {}

void CallibriModule::processCommand(const ByteBuffer &command_packet) noexcept {
    auto command = CallibriCommand::parse(command_packet);
    if (checkIfResponsible(command)){
        handleCommand(command);
    }
    else{
        passToSuccessor(command_packet);
    }
}

std::vector<ByteBuffer> CallibriModule::readData() noexcept {
    decltype(pendingResponses) responsePackets;
    using std::swap;
    swap(pendingResponses, responsePackets);
    return responsePackets;
}

void CallibriModule::pushResponse(const CallibriCommand &response) noexcept {
    pendingResponses.push_back(response.toByteBuffer());
}

void CallibriModule::setSuccessor(std::weak_ptr<CallibriModule> successor) noexcept {
    successorModule = successor;
}

void CallibriModule::passToSuccessor(const ByteBuffer &command_packet) noexcept {
    auto successor = successorModule.lock();
    if (!successor){
        sendNoCommandError();
    }
    else{
        successor->processCommand(command_packet);
    }

}

void CallibriModule::sendNoCommandError() noexcept {
    pushResponse(CallibriCommand(CallibriCommandCode::ERR_CMD, CallibriErrorCode::ERR_NO_CMD, 0xA5B6C7));
}

}
