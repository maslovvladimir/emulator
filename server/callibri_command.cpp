#include "callibri_command.h"

namespace Nes
{

CallibriCommand::CallibriCommand(CommandCode cmd_code, ErrorCode err_code, CallibriAddressType addr) noexcept :
    commandCode(cmd_code),
    errorCode(err_code),
    deviceAddress(addr){

}


ByteBuffer CallibriCommand::toByteBuffer() const noexcept {
    ByteBuffer commandBuffer(PACKET_SIZE);

    //Fill header
    //Set command marker
    ByteInterpreter<unsigned short> marker;
    marker.value = COMMAND_MARKER_VALUE;
    commandBuffer[MARKER_FIRST_BYTE] = marker.bytes[0];
    commandBuffer[MARKER_FIRST_BYTE+1] = marker.bytes[1];

    //Set command number
    commandBuffer[COMMAND_BYTE_INDEX] = static_cast<Byte>(commandCode);

    //Set address
    ByteInterpreter<CallibriAddressType> address;
    address.value = deviceAddress;
    commandBuffer[ADDRESS_FIRST_BYTE] = address.bytes[0];
    commandBuffer[ADDRESS_FIRST_BYTE+1] = address.bytes[1];
    commandBuffer[ADDRESS_FIRST_BYTE+2] = address.bytes[2];

    //Set checksum
    Byte checksum = 0;
    for (auto packetByte = &commandBuffer[0];
         packetByte != &commandBuffer[0] + CHECKSUM_BYTE_POS; checksum -= *packetByte++);
    commandBuffer[CHECKSUM_BYTE_POS] = checksum;

    //Set data
    std::copy(commandData.begin(), commandData.end(), commandBuffer.begin()+DATA_START_INDEX);

    return commandBuffer;
}

CallibriCommandCode CallibriCommand::code() const noexcept {
    return commandCode;
}

CallibriErrorCode CallibriCommand::error() const noexcept {
    return errorCode;
}

CallibriAddressType CallibriCommand::address() const noexcept {
    return deviceAddress;
}

ByteBuffer &CallibriCommand::data() noexcept {
    return commandData;
}

CallibriCommand CallibriCommand::parse(const ByteBuffer &command_packet){
    if (!checkPacketValid(command_packet)){
        return CallibriCommand(CommandCode::ERR_CMD, ErrorCode::ERR_CS);
    }

    auto code = parseGetCode(command_packet);
    if (code == CommandCode::ERR_CMD){
        return CallibriCommand(code, ErrorCode::ERR_NO_CMD);
    }

    auto address = parseGetAddress(command_packet);

    CallibriCommand command(code, ErrorCode::NO_ERROR, address);
    auto& commandDataRef = command.data();
    std::copy(command_packet.begin()+DATA_START_INDEX, command_packet.end(), commandDataRef.begin());

    return command;
}

CallibriCommand::CommandCode CallibriCommand::parseGetCode(const ByteBuffer &command_packet){
    switch (command_packet[COMMAND_BYTE_INDEX])
    {
        case static_cast<unsigned char>(CommandCode::ECHO):
            return CommandCode::ECHO;

        case static_cast<unsigned char>(CommandCode::GET_ADDR):
            return CommandCode::GET_ADDR;

        case static_cast<unsigned char>(CommandCode::GET_AKK_VOLTAGE):
            return CommandCode::GET_AKK_VOLTAGE;

        case static_cast<unsigned char>(CommandCode::BOOT_ACTIVATE_APP):
            return CommandCode::BOOT_ACTIVATE_APP;

        case static_cast<unsigned char>(CommandCode::GET_SENSOR_PARAM):
            return CommandCode::GET_SENSOR_PARAM;

        case static_cast<unsigned char>(CommandCode::START_ADC_DATA_THROW):
            return CommandCode::START_ADC_DATA_THROW;

        case static_cast<unsigned char>(CommandCode::STOP_ADC_DATA_THROW):
            return CommandCode::STOP_ADC_DATA_THROW;

        case static_cast<unsigned char>(CommandCode::SET_FSAM):
            return CommandCode::SET_FSAM;

        case static_cast<unsigned char>(CommandCode::SET_DATA_OFFSET):
            return CommandCode::SET_DATA_OFFSET;

        case static_cast<unsigned char>(CommandCode::SET_PGA_GAIN):
            return CommandCode::SET_PGA_GAIN;

        case static_cast<unsigned char>(CommandCode::START_STIM):
            return CommandCode::START_STIM;

        case static_cast<unsigned char>(CommandCode::STOP_STIM):
            return CommandCode::STOP_STIM;

        case static_cast<unsigned char>(CommandCode::SET_STIM_PARAM):
            return CommandCode::SET_STIM_PARAM;

        case static_cast<unsigned char>(CommandCode::GET_STIM_PARAM):
            return CommandCode::GET_STIM_PARAM;

        case static_cast<unsigned char>(CommandCode::SH_START):
            return CommandCode::SH_START;

        case static_cast<unsigned char>(CommandCode::SH_STOP):
            return CommandCode::SH_STOP;

        case static_cast<unsigned char>(CommandCode::SET_SH_PARAM):
            return CommandCode::SET_SH_PARAM;

        case static_cast<unsigned char>(CommandCode::GET_SH_PARAM):
            return CommandCode::GET_SH_PARAM;

        case static_cast<unsigned char>(CommandCode::GET_SH_AND_STIM_STATE):
            return CommandCode::GET_SH_AND_STIM_STATE;

        case static_cast<unsigned char>(CommandCode::DO_CALIBRATION):
            return CommandCode::DO_CALIBRATION;

        case static_cast<unsigned char>(CommandCode::GET_ELECTRODE_STATE):
            return CommandCode::GET_ELECTRODE_STATE;

        case static_cast<unsigned char>(CommandCode::SWITCH_ADC_INP):
            return CommandCode::SWITCH_ADC_INP;

        case static_cast<unsigned char>(CommandCode::SWITCH_EXT_COM_INPUTS):
            return CommandCode::SWITCH_EXT_COM_INPUTS;

        default:
            return CommandCode::ERR_CMD;
    }
}

CallibriAddressType CallibriCommand::parseGetAddress(const ByteBuffer &command_packet){
    ByteInterpreter<CallibriAddressType> address;
    address.bytes[0] = command_packet[ADDRESS_FIRST_BYTE];
    address.bytes[1] = command_packet[ADDRESS_FIRST_BYTE+1];
    address.bytes[2] = command_packet[ADDRESS_FIRST_BYTE+2];
    return address.value;
}

bool CallibriCommand::checkPacketValid(const ByteBuffer &command_packet) noexcept {
    if (command_packet.size() < PACKET_SIZE)
        return false;


    unsigned char checksum = 0;
    for (auto headerByte = command_packet.data();
         headerByte != command_packet.data() + 8; checksum += *headerByte++);
    if (checksum != 0)
        return false;

    ByteInterpreter<unsigned short> marker;
    marker.bytes[0] = command_packet[MARKER_FIRST_BYTE];
    marker.bytes[1] = command_packet[MARKER_FIRST_BYTE+1];
    if (marker.value != COMMAND_MARKER_VALUE)
        return false;

    return true;
}


}
