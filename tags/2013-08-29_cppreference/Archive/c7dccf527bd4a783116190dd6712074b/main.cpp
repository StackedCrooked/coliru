#include <algorithm>
#include <array>
#include <cassert>
#include <deque>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <typeinfo>
#include <stdint.h>
#include <arpa/inet.h>
#include <cxxabi.h>


std::string Demangle(const char * name)
{
    int st;
    std::shared_ptr<char> p(abi::__cxa_demangle(name, 0, 0, &st), std::free);
    if (st != 0)
    {
        switch (st)
        {
            case -1: throw std::runtime_error("A memory allocation failure occurred.");
            case -2: throw std::runtime_error("Not a valid name under the GCC C++ ABI mangling rules.");
            case -3: throw std::runtime_error("One of the arguments is invalid.");
            default: throw std::runtime_error("Unexpected demangle status");
        }
    }
    return std::string(p.get());
}

template<typename T>
std::string Demangle()
{
    return Demangle(typeid(T).name());
}

#define TRACE std::cout << __PRETTY_FUNCTION__ << std::endl;


typedef std::vector<uint8_t> DynamicBuffer;
typedef std::vector<DynamicBuffer> DynamicBuffers;


class Packet
{
public:
    Packet() = default; // enable default constructor.

    template<typename T>
    explicit Packet(const T & inInitialData)
    {
        push_front(inInitialData);
    }

    explicit Packet(DynamicBuffer inData)
    {
        push_front(std::move(inData));
    }

    // Move constructor.
    Packet(Packet&& inPacket) : mParts(std::move(inPacket.mParts)) { }

    Packet & operator=(Packet && inPacket)
    {
        mParts = std::move(inPacket.mParts);
        return *this;
    }

    void push_front(const uint8_t * inData, std::size_t inSize)
    {
        mParts.push_front(DynamicBuffer(inData, inData + inSize));
    }

    void push_front(const DynamicBuffer & inData)
    {
        mParts.push_front(inData);
    }

    void push_back(const DynamicBuffer & inData)
    {
        mParts.push_back(inData);
    }

    template<typename T>
    void push_front(const T & inHeader)
    {
    	static_assert(std::is_pod<T>::value, "Must be header!");
		const uint8_t * bytes = reinterpret_cast<const uint8_t*>(&inHeader);
        push_front(bytes, sizeof(inHeader));
    }

    std::size_t getTotalSize() const
    {
        auto op = [](std::size_t sum, const DynamicBuffer & str) -> std::size_t {
            return sum + str.size();
        };
        return std::accumulate(mParts.begin(), mParts.end(), 0u, op);
    }

    void get(DynamicBuffer & outData) const
    {
        outData.clear();
        outData.reserve(getTotalSize());

        for (const auto & str : mParts)
        {
            outData.insert(outData.end(), str.begin(), str.end());
        }
    }

    DynamicBuffer getBuffer() const
    {
        DynamicBuffer result;
        get(result);
        return result;
    }

private:
    template<typename T>
    static DynamicBuffer ConvertHeaderToString(const T & inHeader)
    {
        static_assert(std::is_pod<T>::value, "Header type must be POD type!");
        const uint8_t * data = reinterpret_cast<const uint8_t*>(&inHeader);
        return DynamicBuffer(data, data + sizeof(inHeader));
    }

    Packet(const Packet&) = delete; // disable copy
    Packet& operator=(const Packet&) = delete; // disable assigment

    std::deque<DynamicBuffer> mParts;
};


inline DynamicBuffer GetPacketData(const Packet & inPacket)
{
    DynamicBuffer result;
    inPacket.get(result);
    return result;
}



template<typename T>
struct InvalidEnumerator : std::runtime_error
{
    InvalidEnumerator(T t) : std::runtime_error("InvalidEnumerator"), t(t) {}
    ~InvalidEnumerator() throw() {}
    
    T getEnumerator() const
    {
        return t;
    }
    
    T t;
};

template<typename T>
InvalidEnumerator<T> MakeInvalidEnumerator(T t)
{
    return InvalidEnumerator<T>(t);
}

template<typename T, typename /*disambiguator*/>
struct StrongTypedef
{
    template<typename ...Args>
    StrongTypedef(Args && ...args) : data_(std::forward<Args>(args)...) {}
    operator const T & () const
    {
        return data_;
    }
    T & get() { return data_; }
    const T & get() const { return data_; }
    T data_;
};

#define STRONG_TYPEDEF(Type, Name) typedef StrongTypedef<Type, struct Name##_> Name;


uint16_t Net2Host(uint16_t v)
{
    return ntohs(v);
}
uint32_t Net2Host(uint32_t v)
{
    return ntohl(v);
}

template<typename T>
struct NetEncoded
{
    T hostValue() const
    {
        return Net2Host(_value);
    }
    T _value;
};


typedef NetEncoded<uint16_t> Net16;
typedef NetEncoded<uint32_t> Net32;

typedef std::array<uint8_t, 6> MAC;
typedef MAC SourceMAC;
typedef MAC TargetMAC;
typedef MAC LocalMAC;
typedef MAC RemoteMAC;

std::ostream & operator<< (std::ostream & os, const MAC & m)
{
    return os << std::hex
              << std::setw(2) << std::setfill('0') << int(m[0]) << ":"
              << std::setw(2) << std::setfill('0') << int(m[1]) << ":"
              << std::setw(2) << std::setfill('0') << int(m[2]) << ":"
              << std::setw(2) << std::setfill('0') << int(m[3]) << ":"
              << std::setw(2) << std::setfill('0') << int(m[4]) << ":"
              << std::setw(2) << std::setfill('0') << int(m[5]) << std::dec;
}



enum class EtherType : uint16_t
{
    ARP   = 0x0806,
    IP  = 0x0800,
    IP6  = 0x86DD
};

enum class Layer : int
{
    Physical    = 1,
    Network     = 2,
    Internet    = 3,
    Transport   = 4,
    Application = 5
};

std::string Demangle(Layer layer)
{
    switch (layer)
    {        
        #define CASE(Name) case Layer::Name: return #Name;
        CASE(Physical)
        CASE(Network)
        CASE(Internet)
        CASE(Transport)
        CASE(Application)
        default: throw InvalidEnumerator<Layer>(layer);
        #undef CASE
    };
}

constexpr Layer GetHigherLayer(Layer layer)
{
    return layer == Layer::Physical    ? Layer::Network   :
           layer == Layer::Network     ? Layer::Internet  :
           layer == Layer::Internet    ? Layer::Transport :
           Layer::Application;
}

std::ostream& operator<<(std::ostream & os, Layer layer)
{
    return os << Demangle(layer);
}

struct EthernetFrame
{
    Net16 mEtherType;
    TargetMAC mTarget;
    SourceMAC mSource;
};


std::ostream & operator<< (std::ostream & os, EtherType eth)
{
    return os << int(static_cast<uint16_t>(eth));
}


std::ostream & operator<< (std::ostream & os, const EtherType & inEtherType)
{
    switch (inEtherType)
    {
        case EtherType::IP: return os << "IP";
        case EtherType::ARP: return os << "ARP";
        case EtherType::IP6: return os << "IP6";
        default: throw MakeInvalidEnumerator(inEtherType);
    }
}
std::ostream & operator<< (std::ostream & os, const EthernetFrame & inEthernetFrame)
{
    os << "Destination: " << inEthernetFrame.mTarget
       << "\nSource: "    << inEthernetFrame.mSource
       << "\nEtherType: " << inEthernetFrame.mEtherType.hostValue();
    return os;
}

struct VLANTag
{
    Net16 mEtherType;
    uint16_t mData;
};


typedef std::array<uint8_t, 4> IP;
typedef IP SourceIP;
typedef IP TargetIP;
typedef IP LocalIP;
typedef IP RemoteIP;

std::ostream & operator<< (std::ostream & os, const IP & ip)
{
    return os << std::dec
              << int(ip[0]) << "."
              << int(ip[1]) << "."
              << int(ip[2]) << "."
              << int(ip[3]);
}


enum class IPProtNum : uint8_t
{
    ICMP = 1,
    TCP  = 6,
    UDP  = 17
};

struct IPPacket
{
    uint8_t   mVersionAndIHL; // -1
    uint8_t   mTypeOfService; // 1
    Net16     mTotalLength;   // 2
    Net16     mIdentification; // 4
    Net16     mFlagsAndFragmentOffset; // 6
    uint8_t   mTTL; // 8
    IPProtNum mProtocol; // 9
    Net16     mHeaderChecksum; // 10
    SourceIP  mSourceIP; // 12
    TargetIP  mTargetIP; // 16
};


std::ostream & operator<< (std::ostream & os, const IPPacket & ip) { return os << "SourceIP: " << ip.mSourceIP << "\nTargetIP: " << ip.mTargetIP; }


enum class ARPOperation : uint16_t
{
    Request = 1,
    Response = 2
};

struct ARPMessage
{
    Net16 HTYPE;
    Net16 PTYPE;
    uint8_t HLEN;
    uint8_t PLEN;
    Net16 Operation;

    SourceMAC SHA;
    SourceIP  SPA;
    TargetMAC THA;
    TargetIP  TPA;
};

std::ostream & operator<< (std::ostream & os, const ARPMessage & arp)
{
    os << "SHA: " << arp.SHA << "\n";
    os << "SPA: " << arp.SPA << "\n";
    os << "THA: " << arp.THA << "\n";
    os << "TPA: " << arp.TPA << "\n";
    return os;
}
enum class ICMPType : uint8_t
{
    EchoReply   = 0,
    EchoRequest = 8
};

struct ICMPMessage
{
    ICMPType mType;
    uint8_t  mCode;
    Net16 mCheckSum;
    Net16 mIdentifier;
    Net16 mSequenceNumber;
};

std::ostream & operator<< (std::ostream & os, const ICMPType & icmpType) { return os << std::string(icmpType == ICMPType::EchoReply ? "Reply" : "Request"); }
std::ostream & operator<< (std::ostream & os, const ICMPMessage & icmp)  { return os << icmp.mType; }
void Flip(ICMPMessage & msg)
{
    if (msg.mType == ICMPType::EchoRequest)
    {
        msg.mType = ICMPType::EchoReply;
    }
}

struct Payload : std::pair<uint8_t*, uint8_t*>
{
    template<typename ...Args>
    Payload(Args && ...args) : std::pair<uint8_t*, uint8_t*>(std::forward<Args>(args)...) {}
};


Payload Inc(Payload payload, unsigned n)
{
    assert(payload.first + n <= payload.second);
    return Payload(payload.first + n, payload.second);
}

template<typename Header>
Payload Inc(Payload payload)
{
    return Payload(payload.first + sizeof(Header), payload.second);
}

EtherType GetHLPId(EthernetFrame eth)
{
    return static_cast<EtherType>(eth.mEtherType.hostValue());
}

EtherType GetHLPId(VLANTag vlan)
{
    return static_cast<EtherType>(vlan.mEtherType.hostValue());
}

IPProtNum GetHLPId(IPPacket ip)
{
    return static_cast<IPProtNum>(ip.mProtocol);
}

void pop(Payload payload);
void pop(std::pair<Payload, EthernetFrame> msg);
template<typename Tail> void pop(std::pair<Payload, EthernetFrame> msg);
template<typename Tail> void pop(std::pair<Payload, std::pair<IPPacket     , Tail> > msg);
template<typename Tail> void pop(std::pair<Payload, std::pair<ARPMessage   , Tail> > msg);
template<typename Tail> void pop(std::pair<Payload, std::pair<ICMPMessage  , Tail> > msg);

template<typename Head>
std::pair<Payload, Head> Decode(Payload payload)
{
    return std::make_pair(Inc<Head>(payload), *reinterpret_cast<Head*>(payload.first));
}

template<typename Head, typename Tail>
std::pair<Payload, std::pair<Head, Tail> > Decode(const std::pair<Payload, Tail> & msg)
{
    auto p = Decode<Head>(msg.first);
    return std::make_pair(p.first, std::make_pair(p.second, msg.second));
}

void pop(Payload payload)
{
    return pop(Decode<EthernetFrame>(payload));
}

template<typename Header>
auto GetHLPId(std::pair<Payload, Header> msg) -> decltype(GetHLPId(msg.second))
{
    return GetHLPId(msg.second);
}

template<typename Header, typename Tail>
auto GetHLPId(std::pair<Header, Tail> msg) -> decltype(GetHLPId(msg.first))
{
    return GetHLPId(msg.first);
}

void pop(std::pair<Payload, EthernetFrame> msg)
{
    TRACE
    auto hlpId = GetHLPId(msg);
    switch (hlpId)
    {
        case EtherType::ARP:
        {
            pop(Decode<ARPMessage>(msg));
            break;
        }
        case EtherType::IP:
        default:
        {
            pop(Decode<IPPacket>(msg));
            break;
        }
//        default:
//        {
//            throw MakeInvalidEnumerator(hlpId);
//        }
    }
}

template<typename Tail>
void pop(std::pair<Payload, std::pair<IPPacket, Tail> > msg)
{
    TRACE
    auto hlpId = GetHLPId(msg);
    switch (hlpId)
    {
        case IPProtNum::ICMP:
        default:
        {
            pop(Decode<ICMPMessage>(msg));
            break;
        }
//        default:
//        {
//             throw MakeInvalidEnumerator(hlpId);
//        }
    }
}

template<typename T> void Flip(T &) {}

void Flip(EthernetFrame & eth)
{
    using std::swap;
    swap(eth.mSource, eth.mTarget);
}

void Flip(IPPacket & ip)
{
    using std::swap;
    swap(ip.mSourceIP, ip.mTargetIP);
    ip.mFlagsAndFragmentOffset = Net16();
}

void Flip(ARPMessage & arp)
{
    using std::swap;
    swap(arp.SHA, arp.THA);
    swap(arp.SPA, arp.TPA);
}

template<typename T, typename U>
void Flip(std::pair<T, U> & p)
{
    Flip(p.first);
    Flip(p.second);
}

void push(Packet & packet, Payload payload)
{
    std::cout << "Push " << Demangle<Payload>() << ":" << std::endl << (payload.second - payload.first) << std::endl << std::endl;
    packet.push_front(payload.first, payload.second - payload.first);
}

template<typename Header>
void push(Packet & packet, Header hdr)
{
    std::cout << "Push " << Demangle<Header>() << ":" << std::endl << hdr << std::endl << std::endl;
    packet.push_front(hdr);
}

template<typename Head, typename Tail>
void push(Packet & packet, std::pair<Head, Tail> msg)
{
    push(packet, msg.first);
    push(packet, msg.second);
}

template<typename Tail>
void pop(std::pair<Payload, std::pair<ICMPMessage, Tail> > msg)
{
    TRACE
    Flip(msg);
    Packet packet;
    push(packet, msg);
}

template<typename Tail>
void pop(std::pair<Payload, std::pair<ARPMessage, Tail> > msg)
{
    TRACE
    Flip(msg);
    Packet packet;
	push(packet, msg);
}


void run()
{
	auto cPayloadSize = 60;
	auto size = sizeof(EthernetFrame) + sizeof(IPPacket) + sizeof(ICMPMessage) + cPayloadSize;
	DynamicBuffer buffer(size, 0);

	Payload payload(buffer.data(), buffer.data() + buffer.size());
	pop(payload);
}

int main()
{
	run();
    std::cout << GetHigherLayer(Layer::Network) << std::endl;
    std::cout << GetHigherLayer(Layer::Application) << std::endl;
}