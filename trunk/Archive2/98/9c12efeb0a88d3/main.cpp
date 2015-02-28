#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <type_traits>
#include <typeindex>
#include <vector>



struct Packet
{
    Packet(int inSize) : mSize(inSize) {}

    const char* data() const { return nullptr; }

    int size() const { return mSize; }

    int getTimestamp() const { return 0; }

    int mSize;
};


using PacketGroup = std::vector<Packet>;




struct SharedProcessor
{
    template<typename Proc>
    SharedProcessor(std::common_type<Proc>) : mImpl(std::make_shared<Impl<Proc>>()) {}

    void process(const Packet& p)
    {
        mImpl->process_(p);
    }

    void process(const PacketGroup& g)
    {
        mImpl->process_(g);
    }

    template<typename T>
    T& get()
    {
        Concrete<T> concrete;
        mImpl->get(concrete);
        return *concrete.ptr;
    }

private:
    // Utility for getting the inner type via dynamic downcasting.
    struct Abstract { virtual ~Abstract() = default; };
    template<typename T> struct Concrete : Abstract { T* ptr = nullptr; };

    struct Base
    {
        virtual void process_(const Packet&) = 0;
        virtual void process_(const PacketGroup&) = 0;
        virtual void get(Abstract& abstract) = 0;

    protected:
        ~Base() = default;
    };

    template<typename Proc>
    struct Impl final : Base
    {
        Impl() {}

        void process_(const Packet& packet)
        {
            Proc(mConfig, mSnapshot).process(packet);
        }

        void process_(const PacketGroup& group)
        {
            Proc(mConfig, mSnapshot).process(group);
        }

        void get(Abstract& abstract)
        {
            if (&typeid(abstract) == &typeid(Concrete<Snapshot>))
            {
                static_cast<Concrete<Snapshot>&>(abstract).ptr = &mSnapshot;
            }
            else if (&typeid(abstract) == &typeid(Concrete<Config>))
            {
                static_cast<Concrete<Config>&>(abstract).ptr = &mConfig;
            }
            else
            {
                assert(false);
            }
        }

        using Config = typename Proc::Config;
        using Snapshot = typename Proc::Snapshot;

        Config mConfig;
        Snapshot mSnapshot;
    };

    std::shared_ptr<Base> mImpl;
};





struct SimpleCounterTraits
{
    struct Config
    {
        int min_size = 60;
        int max_size = 1500;
    };

    struct Snapshot
    {
        int packets = 0;
        int bytes = 0;
        int badsize[2] = {0};
    };
};


struct SimpleCounter : SimpleCounterTraits
{
    SimpleCounter(const Config& config, Snapshot& snapshot) : config(config), snapshot(snapshot) {}

    void process(const Packet& packet) const
    {
        if (unsigned(packet.size() - config.min_size) <= unsigned(config.max_size - config.min_size))
        {
            snapshot.bytes += packet.size();
            snapshot.packets++;
        }
        else
        {
            snapshot.badsize[packet.size() < config.min_size]++;
        }
    }

    void process(const PacketGroup& group) const
    {
        for (const Packet& packet : group)
        {
            process(packet);
        }
    }

    const Config& config;
    Snapshot& snapshot;
};


int main()
{
    SharedProcessor shared(std::common_type<SimpleCounter>{});
    shared.get<SimpleCounter::Config>().max_size = 100;
    std::cout << shared.get<SimpleCounter::Snapshot>().bytes << std::endl;
    shared.process(Packet(99));
    shared.process(Packet(100));
    shared.process(Packet(101));
    std::cout << shared.get<SimpleCounter::Snapshot>().bytes << std::endl;
}

