#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <assert.h>


// Packet
// - shared storage
// - ~Packet: checks unique -> move to pool


// Storage:


// Pool:
// - be careful for lifetime!
// - 



#define TRACE std::cout << __FILE__ << ":" << __LINE__ << ":0: trace: " << __PRETTY_FUNCTION__ << std::endl;




struct Storage
{   
    std::string mData;
};

typedef void (*RecycleFunction)(std::weak_ptr<void>, Storage&&);

struct Packet
{
    Packet(std::shared_ptr<Storage> storage) : mStorage(std::move(storage)) {}
    
    Packet(Packet&& rhs) :
        mPool(rhs.mPool),
        mRecycleFunction(rhs.mRecycleFunction),
        mStorage(std::move(rhs.mStorage))
    {
        rhs.mPool.reset();
        rhs.mRecycleFunction = nullptr;
    }
    
    Packet& operator=(Packet&& rhs)
    {
        mPool = std::move(rhs.mPool);
        mRecycleFunction = rhs.mRecycleFunction;
        mStorage = std::move(rhs.mStorage);        
        
        rhs.mPool.reset();
        rhs.mRecycleFunction = nullptr;
        assert(!rhs.mStorage);
        return *this;
    }
    
    Packet(const Packet&) = default;
    Packet& operator=(const Packet&) = default;
    
    
    ~Packet()
    {
        if (mStorage && mStorage.unique())
        {
            mRecycleFunction(mPool, std::move(*mStorage));
            mStorage.reset();
        }
    }
    
    void push(const char* s)
    {
        mStorage->mData += s;
    }
    
    const char* data() const
    {
        return mStorage->mData.data();
    }
    
    std::weak_ptr<void> mPool;
    RecycleFunction mRecycleFunction;
    std::shared_ptr<Storage> mStorage;
};


std::vector<Packet> gSocketQueue;


void Send(Packet&& packet)
{
    std::cout << "Sending " << packet.data() << std::endl;
    gSocketQueue.push_back(std::move(packet));
}
struct Sender
{
    Sender() : mSelf(this, [](Sender*){}), mFreeList() {}
    
    static void Recycle(std::weak_ptr<void> weak_ptr, Storage&& storage)
    {
        if (weak_ptr.expired())
        {
            std::cout << "Recycle " << storage.mData << " failed because Sender object was destructed." << std::endl;
            return;
        }
        
        std::shared_ptr<void> void_ptr = weak_ptr.lock();
        Sender& sender = *std::static_pointer_cast<Sender>(void_ptr);
        
        
        std::cout << "Recycle " << storage.mData << std::endl;
        storage.mData.clear();
        sender.mFreeList.push_back(std::move(storage));
    }
    
    ~Sender()
    {
        mFreeList.clear();
    }
    
    void send(const char* s)
    {
        if (mFreeList.empty())
        {
            mFreeList.push_back(Storage());
        }
        
        Packet packet(std::make_shared<Storage>(std::move(mFreeList.back())));
        mFreeList.pop_back();
        packet.mPool = mSelf;
        packet.mRecycleFunction = &Sender::Recycle;
        packet.push(s);
        
        Send(std::move(packet));
        
    }
    
    std::shared_ptr<Sender> mSelf;
    std::vector<Storage> mFreeList;
};


int main()
{
    Sender s;
    s.send("100");
    s.send("200");
    
    std::cout << "Flushing socket." << std::endl;
    
    gSocketQueue.clear();
    
    
    s.send("5000");
    
    std::cout << "End of program." << std::endl;
    
}







