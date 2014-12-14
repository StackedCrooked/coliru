#include <atomic>
#include <algorithm>
#include <cstdint>
#include <vector>
#include <thread>


struct Packet
{
    const std::uint8_t* begin() const;
    const std::uint8_t* end() const;
    std::size_t size() const;
};


struct PacketIterator
{
    const Packet& operator*() const;
    const Packet* operator->() const;
    PacketIterator& operator++();
    friend bool operator==(const PacketIterator& lhs, const PacketIterator& rhs);
    friend bool operator!=(const PacketIterator& lhs, const PacketIterator& rhs);
};


struct SegmentDataPool;


struct SegmentData
{
    SegmentData(SegmentDataPool& inSegmentPool) :
        mSegmentPool(&inSegmentPool),
        mData(1024 * 1024 * 1024), // some kind of default size
        mRefCount(1)
    {
    }

    SegmentData(const SegmentData&) = delete;
    SegmentData& operator=(const SegmentData&) = delete;

    PacketIterator begin() const;
    PacketIterator end() const;

    SegmentDataPool* mSegmentPool;
    std::vector<uint8_t> mData;
    std::atomic<uint32_t> mRefCount;
};


struct SegmentDataPool
{
    SegmentDataPool() {}

    SegmentDataPool(const SegmentDataPool&) = delete;
    SegmentDataPool& operator=(const SegmentDataPool&) = delete;

    ~SegmentDataPool()
    {
        while (!mSegments.empty())
        {
            delete mSegments.back();
            mSegments.pop_back();
        }
    }

    SegmentData& acquire()
    {
        if (mSegments.empty())
        {
            return *new SegmentData(*this);
        }

        auto result = mSegments.back();
        mSegments.pop_back();
        return *result;
    }

    void release(SegmentData& inSegment)
    {
        mSegments.push_back(&inSegment);
    }

private:
    std::vector<SegmentData*> mSegments;
};


struct Segment
{
    Segment(SegmentData& inSegmentData) : mSegment(&inSegmentData)
    {
    }

    Segment(const Segment& rhs) : mSegment(rhs.mSegment)
    {
        mSegment->mRefCount++;
    }

    Segment& operator=(Segment rhs)
    {
        std::swap(mSegment, rhs.mSegment);
        return *this;
    }

    ~Segment()
    {
        if (mSegment->mRefCount > 1)
        {
            mSegment->mRefCount--;
        }
        else
        {
            mSegment->mSegmentPool->release(*mSegment);
        }
    }

    PacketIterator begin() const
    {
        return mSegment->begin();
    }

    PacketIterator end() const
    {
        return mSegment->end();
    }

private:
    SegmentData* mSegment;
};


struct SegmentHandler
{
    void handle_segment(const Segment& segment)
    {
        do_handle_segment(segment);
    }

private:
    virtual void do_handle_segment(const Segment&) = 0;
};


struct Rx
{
    Rx();
    Rx(const Rx&) = delete;
    Rx& operator=(const Rx&) = delete;
    ~Rx();

    void add_segment_handler(SegmentHandler& inHandler)
    {
        mHandlers.push_back(&inHandler);
    }

    void remove_segment_handler(SegmentHandler& inHandler)
    {
        mHandlers.erase(std::remove(mHandlers.begin(), mHandlers.end(), &inHandler), mHandlers.end());
    }

private:
    void run_thread()
    {
        SegmentData& segment = mSegmentPool.acquire();

        // hardware.fill(segment);

        for (SegmentHandler* handler : mHandlers)
        {
            handler->handle_segment(segment);
        }
    }

    SegmentDataPool mSegmentPool;
    std::vector<SegmentHandler*> mHandlers;
    std::thread mThread;
};



// protocolstack
struct Stack
{
    template<typename ...T>
    void pop(T&& ...) {}

    template<typename ...T>
    void dispatch(T&& ...) {}
};


struct PortImpl : SegmentHandler
{
    PortImpl(Rx& inRx) : mRx(inRx)
    {
        inRx.add_segment_handler(*this);
    }

    ~PortImpl()
    {
        mRx.remove_segment_handler(*this);
    }

    void do_handle_segment(const Segment& segment)
    {
        mStack.dispatch(
            [this, segment]
            {
                for (auto& packet : segment)
                {
                    mStack.pop(packet);
                }
                // end of scope: destructor of segment will decrease refcount
            }
        ); // don't wait on returned  std::future
    }


    Rx& mRx;
    Stack mStack;
};




