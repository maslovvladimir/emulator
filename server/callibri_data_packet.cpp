#include "callibri_data_packet.h"

namespace Nes
{

CallibriDataPacket::CallibriDataPacket(unsigned short nmb):packetNumber(nmb){

}

Net::ByteBuffer CallibriDataPacket::toByteBuffer() const noexcept{
    ByteBuffer packet(PACKET_SIZE);
    ByteInterpreter<unsigned short> header;
    header.value = packetNumber;
    packet[0] = header.bytes[0];
    packet[1] = header.bytes[1];
    std::copy(commandData.begin(), commandData.end(), packet.begin()+2);
    return packet;
}

Net::ByteBuffer &CallibriDataPacket::data() noexcept {
    return commandData;
}

}
