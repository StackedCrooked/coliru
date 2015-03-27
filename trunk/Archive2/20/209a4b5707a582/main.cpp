#include <string>
#include <iostream>
#include <vector>
#include <atomic>


using Packet = std::string;


class PacketGroup
{
public:
    PacketGroup() : mImpl(Impl::Allocate()) {}

    PacketGroup(const PacketGroup& rhs) : mImpl(rhs.mImpl)
    {
        if (!mImpl) return;
        mImpl->retain();
    }

    PacketGroup& operator=(const PacketGroup& rhs)
    {
        PacketGroup(rhs).swap(*this);
        return *this;
    }

    PacketGroup(PacketGroup&& rhs) : mImpl(rhs.mImpl)
    {
        rhs.mImpl = nullptr;
    }

    PacketGroup& operator=(PacketGroup&& rhs)
    {
        PacketGroup(std::move(rhs)).swap(*this);
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

    void push_back(const Packet& packet)
    {
        mImpl->mPackets.push_back(packet);
    }

    // todo: iterator support etc..

private:
    struct Impl
    {
        static Impl* Allocate();

        void retain()
        {
            ++mRefCount;
        }

        void release()
        {
            if (! --mRefCount)
            {
                do_release();
            }
        }

        void do_release();

        std::atomic<int> mRefCount{1};
        std::vector<std::string> mPackets;
        
        // other stuff
    };

    Impl* mImpl;
};


// CPP file:
#include <boost/lockfree/stack.hpp>
namespace
{
    enum { PoolCapacity = 300 };
    using Pool = boost::lockfree::stack<void*, boost::lockfree::capacity<PoolCapacity>>; // pool stores void* because it can't access the private type PacketGroup::Impl*
    Pool gPool; // (maybe) todo: delete the objects inside pool at program exit
}


PacketGroup::Impl* PacketGroup::Impl::Allocate()
{
    void* ptr;
    if (!gPool.pop(ptr)) // reuse the Impl object and the storage for the vector
    {
        std::cout << "create new Impl" << std::endl;
        ptr = new Impl;
    }
    else
    {
        std::cout << "recycle an Impl" << std::endl;
    }
    Impl* impl = static_cast<Impl*>(ptr);
    impl->mRefCount = 1;
    return impl;
}


void PacketGroup::Impl::do_release()
{
    mPackets.clear();
    if (!gPool.push(this))
    {
        std::cout << "delete the Impl" << std::endl;
        delete this;
    }
    else
    {        
        std::cout << "save the Impl for later" << std::endl;
    }
}


int main()
{
    PacketGroup group;
    group = group;
    group = std::move(group);
    PacketGroup() = PacketGroup(group);
    PacketGroup() = PacketGroup(group);
    PacketGroup() = PacketGroup(group);
}
