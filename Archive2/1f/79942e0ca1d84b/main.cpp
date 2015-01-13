#include <algorithm>
#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <typeindex>


#define TRACE std::cout << __PRETTY_FUNCTION__ << std::endl;


struct Processor
{
    template<typename T>
    Processor(const T& t) :  mImpl(std::make_shared<Impl<T>>(t))
    {
    }
    
    
    // Provides allocator argument.
    // This enables you to use a memory pool that keeps the processors close together in memory.
    template<typename Alloc, typename T>
    Processor(std::allocator_arg_t, Alloc alloc, const T& t) :  mImpl(std::allocate_shared<Impl<T>>(alloc, t))
    {
    }
    
    
    // Processes a packet.
    // Packet can be anything that meets the following conditions:
    //  - packet.data() must return packet data as const char*
    //  - packet.size() must return packet size
    template<typename Packet>
    void process(const Packet& packet)
    {
        mImpl->process(packet.data(), packet.data() + packet.size());
    }
    
    // Usage example:
    //
    // PacketProcessor& processor = ...
    // SimpleCounter::SnapShot result;
    // processor.get_snapshot(result);
    //
    template<typename Snapshot>
    void get_snapshot(Snapshot& snapshot)
    {
        mImpl->get_snapshot(snapshot);
    }
    
private:
    struct Wrapper
    {
        template<typename Snapshot>
        Wrapper(Snapshot& inSnapshot) : mTypeIndex(typeid(Snapshot)), mPtr(&inSnapshot) {}
        
        template<typename Snapshot>
        void set(const Snapshot& inSnapshot)
        {
            if (mTypeIndex != typeid(Snapshot))
            {
                throw std::bad_cast();
            }
            *static_cast<Snapshot*>(mPtr) = inSnapshot;
        }
        
        std::type_index mTypeIndex;
        void* mPtr;
    };
    
    struct ImplBase
    {
        virtual ~ImplBase() {}
        
        virtual void process(const char* b, const char* e) = 0;
        
        virtual void get_snapshot(Wrapper result) = 0;
    };
    
    template<typename T>
    struct Impl : ImplBase
    {       
        Impl(const T& t) : t(std::move(t)) {}
        
        virtual void process(const char* b, const char* e) override final
        {
            t.process(b, e);
        }
        
        virtual void get_snapshot(Wrapper wrapper) override final
        {
            wrapper.set(t.get_snapshot());
        }
        
        T t;
    };
    
    std::shared_ptr<ImplBase> mImpl;
};


struct SimpleCounter
{    
    struct Snapshot
    {
        std::uint32_t mPackets = 0;
        std::uint32_t mTotalBytes = 0;
    };
    
    void process(const char* b, const char* e)
    {
        mSnapshot.mPackets++;
        mSnapshot.mTotalBytes += static_cast<std::uint32_t>(e - b);
    }
    
    Snapshot get_snapshot() const
    {
        return mSnapshot;
    }
    
    Snapshot mSnapshot;
};


struct SizeCounter
{
    struct Snapshot
    {
        std::uint32_t mMinSize = 0;
        std::uint32_t mMaxSize = 0;
        std::uint32_t mAvgSize = 0;
    };
    
    void process(const char* b, const char* e)
    {
        auto len = static_cast<std::uint32_t>(e - b);
        mSnapshot.mMinSize = mSnapshot.mMinSize == 0 ? len : std::min(mSnapshot.mMinSize, len);
        mSnapshot.mMaxSize = mSnapshot.mMaxSize == 0 ? len : std::max(mSnapshot.mMaxSize, len);
        mSnapshot.mAvgSize = mSnapshot.mAvgSize == 0 ? len : std::uint32_t(0.5 + (9.0 * mSnapshot.mAvgSize + len) / 10);
    }
    
    Snapshot get_snapshot() const
    {
        return mSnapshot;
    }
    
    Snapshot mSnapshot;
};


int main()
{
    std::vector<Processor> processors;
    processors.push_back(SimpleCounter{});
    processors.push_back(SizeCounter{});
    
    std::string packet1 = "123";
    std::string packet2 = "123456789";
    std::string packet3 = "123456";
    
    for (Processor& p :processors)
    {
        p.process(packet1);
        p.process(packet2);
        p.process(packet3);
    }
    
    // Get simple counters
    SimpleCounter::Snapshot simpleCounters;
    
    // Print simple counters
    processors.front().get_snapshot(simpleCounters);
    
    std::cout << "simpleCounters.mPackets=" << simpleCounters.mPackets << std::endl;
    std::cout << "simpleCounters.mTotalBytes=" << simpleCounters.mTotalBytes << std::endl;
    
    
    // Get size counters
    SizeCounter::Snapshot sizeCounters;
    processors.back().get_snapshot(sizeCounters);
    
    // Print size counters
    std::cout << "sizeCounters.mMinSize=" << sizeCounters.mMinSize << std::endl;
    std::cout << "sizeCounters.mMaxSize=" << sizeCounters.mMaxSize << std::endl;
    std::cout << "sizeCounters.mAvgSize=" << sizeCounters.mAvgSize << std::endl;
}

