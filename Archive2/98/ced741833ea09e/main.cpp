#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <vector>


struct Packet;


typedef void (*RecycleFunction)(void*, Packet&);

struct Packet
{
    Packet() : impl()
    {
    }
    
    Packet(void* owner, RecycleFunction recycle) :
        impl(Impl::Create(owner, recycle))
    {
    }
    
    ~Packet()
    {
        // keep the object alive
        auto local_impl = impl;
        
        
        // call .reset while this object is still alive
        impl.reset();
        
        // if this was the last instance then we recycle it
        if (local_impl && local_impl->owner && local_impl.use_count() == 1)
        {
            impl = local_impl;
            impl->recycle_packet(*this);
        }
    }
        
    void push(const std::string& data)
    {
        assert(impl);
        if (!impl)
        {
            impl = Impl::Create(nullptr, nullptr);
        }
        
        impl->data.insert(impl->data.end(), data.begin(), data.end());
    }
    
    struct Impl
    {
        static std::shared_ptr<Impl> Create(void* owner, RecycleFunction recycle)
        {
            return std::make_shared<Impl>(owner, recycle);
        }
        
        Impl(void* owner, RecycleFunction recycle) :
            owner(owner),
            recycle(recycle)
        {
        }
        
        ~Impl()
        {
            
        }
        
        void recycle_packet(Packet& packet)
        {
            std::cout << "Recycling: " << packet.impl->data << std::endl;
            data.clear();
            recycle(owner, packet);
        }
        
        void* owner;
        RecycleFunction recycle;
        std::string data;
    };
    std::shared_ptr<Impl> impl;
};

std::vector<Packet> socket_queue;
void Send(Packet& packet)
{    
    std::cout << "Sending packet: " << packet.impl->data << std::endl;
    socket_queue.push_back(packet);
}


struct Sender
{
    void send(const char* s)
    {
        if (mPool.empty())
        {
            mPool.emplace_back(nullptr, &Sender::Recycle);
        }
        
        Packet packet = mPool.back();
        mPool.pop_back();
        
        packet.impl->owner = this;
        packet.push(s);
        
        Send(packet);
    }
    
    static void Recycle(void* owner, Packet& p)
    {
        p.impl->owner = nullptr; // disable the recylation of unused packets
        static_cast<Sender*>(owner)->mPool.push_back(p);
    }
    
    std::vector<Packet> mPool;
};


int main()
{
        Sender sender;
        sender.send("a");
        sender.send("b");
}