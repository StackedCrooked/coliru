#include <atomic>
#include <iostream>
#include <vector>


class PacketGroup
{
public:
    PacketGroup() : mImpl(new Impl) {}

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
    // todo: iterator support etc..

private:
    struct Impl
    {
        void retain()
        {
            ++mRefCount;
        }

        void release()
        {
            if (! --mRefCount)
            {
                delete this;
            }
        }

        std::atomic<int> mRefCount{1};
    };

    Impl* mImpl;
};


int main()
{
    PacketGroup group;
    group = group;
    group = std::move(group);
    PacketGroup() = PacketGroup(group);
}
