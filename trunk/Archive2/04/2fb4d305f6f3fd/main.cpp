#include "tbb/concurrent_queue.h"
#include <array>
#include <iostream>
#include <string>
#include <assert.h>
#include <string.h>


struct Packet
{
    Packet() : mData(), mBegin(sizeof(mData)) {}
    Packet(const Packet&) = delete;
    Packet& operator=(const Packet&) = delete;
    
    void prepend(const void* bytes, unsigned len)    
    {
        assert(mBegin >= len);
        memcpy(data(), bytes, len);
        mBegin -= len;
    }
    
    template<typename T>
    void prepend(const T& t)
    {
        static_assert(std::is_pod<T>::value, "T must be POD");
        prepend(&t, sizeof(t));
    }
    
    uint8_t* data()
    {
        return &mData[0] + mBegin;
    }
    
    const uint8_t* data() const
    {
        return &mData[0] + mBegin;
    }
    
    unsigned size() const
    {
        return sizeof(mData) - mBegin;
    }
    
private:
    std::array<uint8_t, 1600> mData;
    unsigned mBegin;
};


struct Bucket
{
    typedef void(*NotifyRelease)(const Bucket&);
    
    Bucket(NotifyRelease inNotifyRelease = NotifyRelease()) : mNotifyRelease(inNotifyRelease), mPackets(), mSize() {}
    
    void setNotifyRelease(const NotifyRelease& inNotifyRelease)
    {
        mNotifyRelease = inNotifyRelease;
    }
    
    void release()
    {
        if (mNotifyRelease)
        {
            mNotifyRelease(*this);
        }
    }
    
    void push_back(Packet& packet)
    {
        assert(mSize < Capacity);
        mPackets[mSize++] = &packet;
    }
    
    unsigned size() const { return mSize; }
    
    const Packet* begin() const { return mPackets[0]; }    
    const Packet* end() const { return begin() + size(); }
    
    void clear()
    {
        mSize = 0;
    }
    
    bool empty() const { return !size(); }    
    
    bool full() const { return mSize == Capacity; }
    
private:
    enum { Capacity = 10 };    
    NotifyRelease mNotifyRelease;
    std::array<Packet*, Capacity> mPackets;
    unsigned mSize;    
};



typedef tbb::concurrent_bounded_queue<Bucket> Buckets;


int main()
{
    Buckets buckets;
    Packet packet;
    
    Bucket bucket([](const Bucket& b){
        std::cout << "Released " << b.size() << " packets." << std::endl;
    });
    if (bucket.full())
    {
        buckets.push(bucket);
        bucket.clear();
    }
    
    bucket.push_back(packet);
    
    bucket.release();
}


