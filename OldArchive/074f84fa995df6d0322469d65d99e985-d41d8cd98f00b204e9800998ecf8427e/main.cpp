class Packet;
typedef std::bitset<8> TCPFlags;
typedef uint16_t TCPSourcePort;
typedef uint16_t TCPDestinationPort;
typedef uint32_t TCPSequenceNumber;
typedef uint32_t TCPAcknowledgmentNumber;
typedef uint16_t TCPWindowSize;
typedef uint16_t TCPUrgentPointer;
typedef std::vector<uint32_t> TCPOptions;

void MakeTCPSegment(Packet & ioPacket,
                   TCPSourcePort,
                   TCPDestinationPort,
                   IPv4SourceAddress,
                   IPv4DestinationAddress,
                   TCPSequenceNumber,
                   TCPAcknowledgmentNumber,
                   TCPWindowSize,
                   TCPUrgentPointer,
                   const TCPFlags&,
                   const TCPOptions&);