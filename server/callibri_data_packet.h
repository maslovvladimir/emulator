#ifndef CALLIBRI_DATA_PACKET_H
#define CALLIBRI_DATA_PACKET_H

#include "callibri_command.h"

namespace Nes
{

class CallibriDataPacket : public CallibriCommand{
public:
    CallibriDataPacket(unsigned short);
    ByteBuffer toByteBuffer() const noexcept override;
    ByteBuffer& data() noexcept override;
private:
    static constexpr ByteBuffer::size_type PACKET_SIZE = 20;
    static constexpr ByteBuffer::size_type DATA_LENGTH = 18;
    ByteBuffer commandData = ByteBuffer(DATA_LENGTH);
    unsigned short packetNumber;
};

}
#endif // CALLIBRI_DATA_PACKET_H
