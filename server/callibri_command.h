#ifndef CALLIBRI_COMMAND_H
#define CALLIBRI_COMMAND_H

#include "nes_types.h"
#include <memory>

namespace Nes
{

enum class CallibriMode : int {
    BOOTLOADER,
    APPLICATION
};

template <typename T>
union ByteInterpreter
{
    T value;
    Byte bytes[sizeof(T)];
};


using CallibriAddressType = unsigned long;

class CallibriCommand{
public:

    enum class CommandCode : Byte {
        ERR_CMD = 0x00,
        ECHO = 0xA0,
        GET_ADDR = 0xA1,
        GET_AKK_VOLTAGE = 0xA4,        
        SWITCH_FILTER_STATE = 0x09,
        GET_SENSOR_PARAM = 0x24,
        APP_ACTIVATE_BOOT = 0x56,
        BOOT_ACTIVATE_APP = 0x54,
        START_ADC_DATA_THROW = 0x40,
        STOP_ADC_DATA_THROW = 0x41,
        SET_FSAM = 0x03,
        SET_DATA_OFFSET = 0x21,
        SET_PGA_GAIN = 0x0D,
        START_STIM = 0x11,
        STOP_STIM = 0x12,
        SET_STIM_PARAM = 0x13,
        GET_STIM_PARAM = 0x15,
        SH_START = 0x71,
        SH_STOP = 0x72,
        SET_SH_PARAM = 0x70,
        GET_SH_PARAM = 0x73,
        GET_SH_AND_STIM_STATE = 0x17,
        DO_CALIBRATION = 0x16,
        GET_ELECTRODE_STATE = 0x46,
        SWITCH_ADC_INP = 0x0A,
        SWITCH_EXT_COM_INPUTS = 0x23
    };

    enum class ErrorCode : Byte {
        NO_ERROR = 0x00,
        ERR_NO_CMD = 0x21,
        ERR_WRONG_PARAM = 0x25,
        ERR_CS = 0x23,
        ADC_TIMEOUT_ERROR = 0x26
    };

    CallibriCommand(CommandCode cmd = CommandCode::ERR_CMD,
                    ErrorCode err = ErrorCode::NO_ERROR,
                    CallibriAddressType addr = 0) noexcept;

    virtual ByteBuffer toByteBuffer() const noexcept;
    CommandCode code() const noexcept;
    ErrorCode error() const noexcept;
    CallibriAddressType address() const noexcept;
    virtual ByteBuffer& data() noexcept;

    static CallibriCommand parse(const ByteBuffer &);

private:
    static constexpr ByteBuffer::size_type PACKET_SIZE = 20;
    static constexpr ByteBuffer::size_type CHECKSUM_BYTE_POS = 7;
    static constexpr ByteBuffer::size_type DATA_START_INDEX = 8;
    static constexpr ByteBuffer::size_type DATA_LENGTH = 12;
    static constexpr ByteBuffer::size_type ADDRESS_FIRST_BYTE = 4;
    static constexpr ByteBuffer::size_type MARKER_FIRST_BYTE = 0;
    static constexpr ByteBuffer::size_type COMMAND_BYTE_INDEX = 3;
    static constexpr unsigned short int COMMAND_MARKER_VALUE = 65503;

    static bool checkPacketValid(const ByteBuffer &) noexcept;
    static CommandCode parseGetCode(const ByteBuffer &);
    static CallibriAddressType parseGetAddress(const ByteBuffer &);

    const CommandCode commandCode;
    const ErrorCode errorCode;
    const CallibriAddressType deviceAddress;
    ByteBuffer commandData = ByteBuffer(DATA_LENGTH);
};

using CallibriCommandCode = CallibriCommand::CommandCode;
using CallibriErrorCode = CallibriCommand::ErrorCode;

}

#endif // CALLIBRI_COMMAND_H
