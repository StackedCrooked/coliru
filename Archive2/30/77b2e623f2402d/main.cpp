

using PacketSize = std::uint16_t;
using PacketCount = std::int64_t;
using Timestamp = std::int64_t;
using SizeCounters = FlatMap<PacketSize, PacketCount>;


struct Packet
{
    template<typename PacketType>
    explicit Packet(const PacketType& inPacket) :
        mData(GetData(inPacket)),
        mSize(GetSize(inPacket)),
        mTimestamp(GetTimestamp(inPacket))
    {
    }
    
    const unsigned char* data() const
    {
        return mData;
    }
    
    PacketSize size() const
    {
        return mPacketSize;
    }
    
    Timestamp timestamp() const
    {
        return mTimestamp;
    }
    
    const unsigned char* mData;
    PacketSize mPacketSize;
    Timestamp mTimestamp;
};


using PacketGroup = std::vector<Packet>;



struct Processor
{
    template<typename T>
    explicit Processor(T t) : mImpl(std::make_shared<Impl<T>>(t))
    {
    }
    
    void process(const Packet& packet)
    {
        mImpl->process(packet);
    }
    
    void process(const PacketGroup& group)
    {
        mImpl->process(group);
    }
    
private:
    struct Base
    {
        virtual void process(const Packet&) =  0;
        virtual void process(const PacketGroup&) =  0;
    };
    
    template<typename T>
    struct Impl
    {
        explicit Impl(T t) : t(t) {}
        
        virtual void process(const Packet& packet)
        {
            Process(t, packet);
        }
        
        virtual void process(const PacketGroup& group)
        {
            Process(t, group);
        }
        
        T t;
    };
    
    std::shared_ptr<Base> mImpl;
    
};


template<typename ProcessorType>
void Process(ProcessorType& proc, const Packet& packet)
{
    proc.process(packet);
}


template<typename ProcessorType>
void Process(ProcessorType& proc, const PacketGroup& group)
{
    for (const auto& packet : group)
    {
        Process(proc, packet);
    }
}


struct RateCounter
{
    RateCounter(PacketSize min_size, PacketSize max_size) :
        mMinSize(min_size),
        mMaxSize(max_size)
    {
    }
    
    struct Snapshot
    {
        PacketCount mUndersized = 0;
        PacketCount mOversized = 0;
        SizeCounters mCounters;
    };
    
    void process(const Packet& packet)
    {
        auto size = packet.size();
        if (size < mMinSize)
        {
            mSnapshot.mUndersized++;
        }
        else if (size < mMaxSize)
        {
            mSnapshot.mOversized++;
        }
        else
        {
            mSnapshot.mCounters[size]++;
        }
    }
    
    PacketSize mMinSize = 60;
    PacketSize mMaxSize = 1500;
    Snapshot mSnapshot;
};


struct RxPacket
{
};


PacketData GetData(RxPacket& rxPacket)
{
    return rxPacket.GetFrame();
}

PacketSize GetSize(RxPacket& rxPacket)
{
    return rxPacket.GetWireLength() - ::balh::ETHERNET_FCS;
}


Timestamp GetTimestamp(RxPacket& rxPacket)
{
    return rxPacket.GetTimestampNS();
}



void test()
{
    std::vector<Processor> processors;
    processors.push_back(Processor(RateCounter()));
    processors.push_back(Processor(RateCounter()));
    
    Packet packet;
    for (auto& proc : processors)
    {
        Process(proc, packet);
    }
    
    PacketGroup group;
    for (auto& proc : processors)
    {
        Process(proc, group);
    }
}
