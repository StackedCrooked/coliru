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
    typedef void (*RecycleFunction)(std::weak_ptr<void> weak_ptr, Storage&&);
    
    void setPool(std::weak_ptr<void> pool_ptr, RecycleFunction f)
    {
        mPool = pool_ptr;
        mRecycleFunction = f;
    }
    
    std::weak_ptr<void> mPool;
    RecycleFunction mRecycleFunction;
    std::string mData;
};


struct Packet
{
    Packet(std::shared_ptr<Storage> storage) : mStorage(std::move(storage)) {}
    
    Packet(Packet&&) = default;
    Packet& operator=(Packet&&) = default;
    
    Packet(const Packet&) = default;
    Packet& operator=(const Packet&) = default;
    
    
    ~Packet()
    {
        if (mStorage && mStorage.unique())
        {
            auto recycle = mStorage->mRecycleFunction; 
            auto pool = mStorage->mPool;
            recycle(pool, std::move(*mStorage));
            mStorage.reset();
        }
    }
    
    void setPool(std::weak_ptr<void> pool_ptr, Storage::RecycleFunction f)
    {
        mStorage->setPool(pool_ptr, f);
    }
    
    void push(const char* s)
    {
        mStorage->mData += s;
    }
    
    const char* data() const
    {
        return mStorage->mData.data();
    }
    
private:
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
        packet.setPool(mSelf, &Sender::Recycle);
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







