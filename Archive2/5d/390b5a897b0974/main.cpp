#include <boost/lockfree/stack.hpp>
#include <atomic>
#include <cstdint>
#include <memory>
#include <vector>


struct Packet
{
    int GetHash() const;
};


// TODO: Maybe put details in PacketGroupBase (base class)
struct PacketGroup
{
    struct Impl
    {
        void acquire()
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
    
    PacketGroup() = default;
    
    void init(Impl* inImpl)
    {
        mImpl = inImpl;
    }
    
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
        mImpl->acquire();
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
    struct PacketGroupImpl : PacketGroup::Impl
    {
        void do_release()
        {
            mRefCount = 0;
            mPackets.clear();
            mSegmentOwner.reset();
            Get().push(this);
        }
        
        std::shared_ptr<void> mSegmentOwner;
    };

    using Pool = boost::lockfree::stack<PacketGroupImpl*>;
    
    static Pool& Get()
    {
        static Pool fPool;
        return fPool;
    }
    
    static PacketGroupImpl* Acquire()
    {
        PacketGroupImpl* group;
        if (!Get().pop(group))
        {
            group = new PacketGroupImpl;
        }
        
        group->mRefCount = 1;
        return group;
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
            if (!group.mImpl)
            {
                PacketGroupPool::PacketGroupImpl* impl = PacketGroupPool::Acquire();
                impl->mSegmentOwner = consumer;
                group.init(impl);
            }
            group.mImpl->mPackets.push_back(&packet);
        }
        
        
        for (auto i = 0ul; i != num_interfaces; ++i)
        {
            std::vector<PacketProcessor*>& processors = mProcessors[i];
            for (PacketProcessor* processor : processors)
            {
                processor->ProcessGroup(mGroups[i]);
            }
            
            mGroups.clear();
            mGroups.resize(mGroups.capacity());
        }
    }
    
    std::vector<PacketGroup> mGroups;
    std::vector<std::vector<PacketProcessor*>> mProcessors;
};
