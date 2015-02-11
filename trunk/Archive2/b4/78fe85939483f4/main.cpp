#include <boost/lockfree/stack.hpp>
#include <atomic>
#include <cstdint>
#include <memory>
#include <vector>


struct Packet
{
    int GetHash() const;
};


// PacketGroup is a handle to a group of packets.
// Each copy of the group extends the lifetime of the parent "segment".
// Once all copies have gone out of scope, then the segment will be released as well.
struct PacketGroup
{
    PacketGroup() : mImpl() {}
    
    PacketGroup(PacketGroup&& rhs) :
        mImpl(rhs.mImpl)
    {
        rhs.mImpl = nullptr;
    }
    
    PacketGroup& operator=(PacketGroup&& rhs)
    {
        PacketGroup(std::move(rhs)).swap(*this);
        return *this;
    }
    
    PacketGroup(const PacketGroup& rhs) :
        mImpl(rhs.mImpl)
    {
        if (!mImpl) return;
        mImpl->duplicate();
    }
    
    PacketGroup& operator=(const PacketGroup& rhs)
    {
        PacketGroup(rhs).swap(*this);
        return *this;
    }
    
    ~PacketGroup()
    {
        if (!mImpl) return;
        mImpl->release();
    }
    
    void swap(PacketGroup& rhs)
    {
        using std::swap;
        swap(mImpl, rhs.mImpl);
    }
    
    // Helper
    struct const_iterator
    {
        explicit const_iterator(std::vector<const Packet*>::const_iterator it) : it(it) { }
        const_iterator(const_iterator&&) = default;
        const_iterator& operator=(const_iterator&&) = default;
        const_iterator(const const_iterator&) = default;
        const_iterator& operator=(const const_iterator&) = default;
        ~const_iterator() = default;
        const Packet& operator*() { return **it; }
        const_iterator& operator++() { ++it; return *this;}
        friend bool operator==(const_iterator lhs, const_iterator rhs) { return lhs.it == rhs.it; }
        friend bool operator!=(const_iterator lhs, const_iterator rhs) { return !(lhs == rhs); }
        std::vector<const Packet*>::const_iterator it;
    };
    
    const_iterator begin() const { return const_iterator(mImpl->mPackets.begin()); }
    const_iterator end() const { return const_iterator(mImpl->mPackets.end()); }
    
private:
    friend struct PacketGroupPool;
    
    struct Impl
    {        
        Impl() {}
        
        Impl(const Impl&) = delete;
        Impl& operator=(const Impl&) = delete;
        
        virtual ~Impl() = default;
        
        void duplicate()
        {
            mRefCount++;
        }
        
        void release()
        {
            if (!--mRefCount)
            {
                do_release();
            }
        }
        
        virtual void do_release() = 0;
        
        std::atomic<std::uint32_t> mRefCount{1};
        std::vector<const Packet*> mPackets;
    };
      
private:
    Impl* mImpl;
};


struct PacketProcessor
{
    PacketProcessor() = default;
    PacketProcessor(const PacketProcessor&) = delete;
    PacketProcessor& operator=(const PacketProcessor&) = delete;    
    virtual ~PacketProcessor() = default;
    
    virtual void ProcessGroup(const PacketGroup& inPacketGroup)
    {
        for (const Packet& packet : inPacketGroup)
        {
            Process(packet);
            
        }
    }
    
    virtual void Process(const Packet& packet) = 0;
};


class PacketProcessorManager : public PacketProcessor
{
public:
    virtual void Process(const Packet& packet) override final
    {
    }
};

struct PacketGroupPool
{
    template<typename Consumer>
    static void AddPacket(PacketGroup& inGroup, const Packet& inPacket, const std::shared_ptr<Consumer>& inConsumer)
    {
        if (!inGroup.mImpl)
        {
            PacketGroupImpl* impl;
            if (!Get().pop(impl))
            {
                impl = new PacketGroupImpl;
            }
            assert(impl->mRefCount == 0);
            impl->mRefCount = 1;
            impl->mConsumer = inConsumer;
            inGroup.mImpl = impl;
        }
        inGroup.mImpl->mPackets.push_back(&inPacket);
    }
    
    static bool Check(const PacketGroup& inGroup)
    {
        return inGroup.mImpl;
    }

private:
    struct PacketGroupImpl : PacketGroup::Impl
    {
        void do_release()
        {
            mRefCount = 0;
            mPackets.clear();
            mConsumer.reset();
            Get().push(this);
        }
        
        std::shared_ptr<void> mConsumer;
    };
    
    using Pool = boost::lockfree::stack<PacketGroupImpl*>;
    
    static Pool& Get()
    {
        static Pool fPool;
        return fPool;
    }
};


struct Consumer
{
    const Packet* begin();
    const Packet* end();
};

struct HighPriorityProcessor
{
    enum { num_interfaces = 10 };
    
    HighPriorityProcessor()
    {
        mGroups.reserve(num_interfaces);
        mProcessors.reserve(num_interfaces);
    }

    Consumer* get_consumer();

    void process_segment()
    {
        std::shared_ptr<Consumer> consumer{get_consumer()};
        
        for (const Packet& packet : *consumer)
        {
            PacketGroup& group = mGroups[packet.GetHash()];
            PacketGroupPool::AddPacket(group, packet, consumer);
        }
        
        for (auto i = 0ul; i != num_interfaces; ++i)
        {
            std::vector<PacketProcessor*>& processors = mProcessors[i];
            for (PacketProcessor* processor : processors)
            {
                PacketGroup& group = mGroups[i];
                if (PacketGroupPool::Check(group))
                {
                    processor->ProcessGroup(group);
                }
            }
            
            mGroups.clear();
            mGroups.resize(mGroups.capacity());
        }
    }
    
    std::vector<PacketGroup> mGroups;
    std::vector<std::vector<PacketProcessor*>> mProcessors;
};
