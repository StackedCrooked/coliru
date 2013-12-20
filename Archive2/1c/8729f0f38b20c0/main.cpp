#include <iostream>
#include <memory>
#include <string>
#include <vector>


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
    typedef void (*RecycleFunction)(void*, Storage&&);
    
    Storage(void* inPool, RecycleFunction inRecycleFunction) : mPool(inPool), mRecycleFunction(inRecycleFunction) {}
    
    Storage(const Storage&) = delete;
    
    Storage(Storage&& rhs) :
        mPool(rhs.mPool),
        mRecycleFunction(rhs.mRecycleFunction),
        mData(std::move(rhs.mData))
    {
        rhs.mPool = nullptr;
        rhs.mRecycleFunction = nullptr;
    }

    void recycle()
    {
        if (mRecycleFunction)
        {
            auto r = mRecycleFunction; mRecycleFunction = nullptr;
            auto p = mPool; mPool = nullptr;
            r(p, std::move(*this));
        }
    }
    
    
    void* mPool;
    RecycleFunction mRecycleFunction;
    std::string mData;
};


struct Packet
{
    Packet(std::shared_ptr<Storage> storage) : mStorage(std::move(storage)) {}
    
    
    ~Packet()
    {
        if (mStorage && mStorage.unique())
        {
            mStorage->recycle();
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
    
    std::shared_ptr<Storage> mStorage;
};


struct Sender
{
    static void Recycle(void* sender, Storage&& storage)
    {
        std::cout << "Recycle " << storage.mData << ". New FreeList size: " << (static_cast<Sender*>(sender)->mFreeList.size() + 1) << std::endl;
        storage.mRecycleFunction = nullptr;
        storage.mData.clear();
        static_cast<Sender*>(sender)->mFreeList.push_back(std::move(storage));
    }
    
    ~Sender()
    {
        mFreeList.clear();
    }
    
    void send(const char* s)
    {
        if (mFreeList.empty())
        {
            std::cout << "Grow FreeList" << std::endl;
            mFreeList.push_back(Storage(this, &Sender::Recycle));
        }
        
        Packet packet(std::make_shared<Storage>(std::move(mFreeList.back())));
        mFreeList.pop_back();
        packet.mStorage->mPool = this;
        packet.mStorage->mRecycleFunction = &Sender::Recycle;
        packet.push(s);
        
        std::cout << "Sending " << packet.data() << std::endl;
        
    }
    
    std::vector<Storage> mFreeList;
};


int main()
{
    Sender s;
    s.send("a");
    s.send("b");
    s.send("c");
    s.send("d");
    s.send("e");
    s.send("f");
    s.send("g");
    s.send("h");
}







