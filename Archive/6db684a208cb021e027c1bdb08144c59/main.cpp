#include <iostream>


template<typename LLDecoder>
struct Decoder
{
    Decoder(LLDecoder & inLLDecoder) : mLLDecoder(&inLLDecoder) {}
    LLDecoder * mLLDecoder;
};


struct L1Decoder
{
    L1Decoder(const char * data, unsigned length) : data(data), length(length) {}
    const char * data;
    unsigned length;
};


struct EthernetDecoder : Decoder
{
    
};

STRONG_TYPEDEF(IncomingData, Ethernet)
STRONG_TYPEDEF(IncomingData, VLANFrame)
STRONG_TYPEDEF(IncomingData, IPv4Packet)
STRONG_TYPEDEF(IncomingData, IPv6Packet)
STRONG_TYPEDEF(IncomingData, ICMPMessage)
STRONG_TYPEDEF(IncomingData, TCPSegment)


void pop(EthernetDecoder)