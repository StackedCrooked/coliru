#include <iostream>

template<typename T, typename /*disambiguator*/>
struct StrongTypedef {
    StrongTypedef(const T & data = T()) : data_(data) {}
    operator const T&() const { return data_; }
    T data_;
};

#define STRONG_TYPEDEF(Type, Name) typedef StrongTypedef<Type, struct Name##_> Name;

template<typename LLDecoder>
struct Decoder {
    Decoder(const LLDecoder & inLLDecoder) : mLLDecoder(&inLLDecoder) {}
    LLDecoder * mLLDecoder;
};

struct L1Decoder {
    L1Decoder(const char * data, unsigned length) : data(data), length(length) {}
    const char * data;
    unsigned length;
};

template<typename LLDecoder, typename Header>
struct GenericDecoder : Decoder<LLDecoder> {
    GenericDecoder(const LLDecoder & inLLDecoder) :
        Decoder<LLDecoder>(inLLDecoder),
        mHeader(Decode<Header>(GetPayload(inLLDecoder)))
    {
    }
    
    Header mHeader;
};

struct EthernetHeader
{
    unsigned short mEtherType;
    unsigned char mDestination[6];
    unsigned char mSource[6];
};

struct VLANTag
{
    unsigned short mEtherType;
    unsigned char data[12];
};

struct IPv4Header
{
    unsigned char data[20];
};

typedef GenericDecoder<EthernetHeader> EthernetDecoder;
typedef GenericDecoder<VLANHeader> VLANDecoder;
typedef GenericDecoder<IPv4Header> IPv4Decoder;


