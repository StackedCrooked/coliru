#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <vector>


struct Packet;


typedef void (*RecycleFunction)(void*, Packet&&);

struct Packet
{
    Packet() : impl()
    {
    }

    Packet(void* pool, RecycleFunction recycle) :
        impl(Impl::Create(pool, recycle))
    {
    }

    ~Packet()
    {
        if (!impl)
        {
            return;
        }
        
        if (!impl->pool)
        {
            return;
        }

        // keep the object alive
        auto local_impl = impl;

        // destroy impl
        impl.reset();

        // check use count of local object (should be thread safe?)
        if (local_impl.use_count() == 1)
        {
            // re-assign impl
            impl = local_impl;
            impl->recycle_packet(std::move(*this)); //
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
        static std::shared_ptr<Impl> Create(void* pool, RecycleFunction recycle)
        {
            return std::make_shared<Impl>(pool, recycle);
        }

        Impl(void* pool, RecycleFunction recycle) :
            pool(pool),
            recycle(recycle)
        {
        }

        ~Impl()
        {

        }

        void recycle_packet(Packet&& packet)
        {
            std::cout << "Recycle " << packet.impl->data << std::endl;
            data.clear();
            recycle(pool, std::move(packet));
        }

        void* pool;
        RecycleFunction recycle;
        std::string data;
    };
    std::shared_ptr<Impl> impl;
};


std::vector<Packet> socket_queue;

void Send(Packet& packet)
{
    std::cout << "Sending " << packet.impl->data << std::endl;
    socket_queue.push_back(packet);
}


void Flush()
{
    std::cout << "Flush!" << std::endl;
    socket_queue.clear();
}


enum class RequireAck { Yes, No };


struct Sender
{
    
    void send(const char* s, RequireAck require_ack)
    {
        if (mPool.empty())
        {
            mPool.emplace_back(nullptr, &Sender::Recycle);
        }

        Packet packet = std::move(mPool.back());
        mPool.pop_back();

        packet.impl->pool = this;
        packet.push(s);
        
        if (require_ack == RequireAck::Yes)
        {
            // store unacked copy
            mUnacked.push_back(packet);
        }

        Send(packet);
    }
    
    void retransmit_unacked()
    {
        for (auto& unacked : mUnacked)
        {
            std::cout << "Schedule retransmit for " << unacked.impl->data << std::endl;
            Send(unacked);
        }
    }
    
    void ack_all()
    {
        for (auto& unacked : mUnacked)
        {
            std::cout << "Recieved ack for " << unacked.impl->data << std::endl;
        }
        mUnacked.clear();
    }

    static void Recycle(void* pool, Packet&& p)
    {
        p.impl->pool = nullptr; // disable the recyclation of unused packets
        static_cast<Sender*>(pool)->mPool.push_back(std::move(p));
    }

    std::vector<Packet> mPool;
    std::vector<Packet> mUnacked;
};


int main()
{
    Sender sender;
    sender.send("udp-1", RequireAck::No);
    sender.send("tcp-1", RequireAck::Yes);

    Flush();
        
    sender.retransmit_unacked();
        
    sender.send("udp-2", RequireAck::No);
    sender.send("tcp-2", RequireAck::Yes);
        
    Flush();
    
    sender.ack_all();
    
}
