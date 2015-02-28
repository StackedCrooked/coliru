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


// SharedProcessor is a essentially a shared-ptr wrapper for actual processors.
// This is important because with the new async processing. This is needed to
// ensure the processor stays alive when the API destroys it while there are
// still threads working on it in the background.
struct SharedProcessor
{
    // The (empty) traits object is passed by value here. (It just serves as a type tag.)
    // Traits::Processor is the actual processor type.
    template<typename Traits>
    SharedProcessor(Traits) : mImpl(std::make_shared<Impl<typename Traits::Processor>>()) {}

    void process(const Packet& p) { mImpl->process_(p); }

    void process(const PacketGroup& g) { mImpl->process_(g); }

    // Getter for the Config and Snapshot objects.
    // Example: processor.get<SimpleCounter::Config>().min_size = 1;
    template<typename T>
    T& get() {
        Concrete<T> concrete;
        mImpl->get(concrete);
        return *concrete.ptr;
    }

private:
    // Utility for enabling dynamic cast on the (non-polymorphic) Config and Snapshot objects.
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
        { Proc(mConfig, mSnapshot).process(packet); }

        void process_(const PacketGroup& group)
        { Proc(mConfig, mSnapshot).process(group); }

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
    typedef struct SimpleCounter Processor; // actually a forward declaration in parent scope

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
        snapshot.packets += group.size();
        for (const Packet& packet : group)
        {
            if (unsigned(packet.size() - config.min_size) <= unsigned(config.max_size - config.min_size))
            {
                snapshot.bytes += packet.size();
            }
            else
            {
                snapshot.badsize[packet.size() < config.min_size]++;
            }
        }
    }

    const Config& config;
    Snapshot& snapshot;
};


int main()
{
    SharedProcessor shared(SimpleCounterTraits{});
    
    // getting the config
    shared.get<SimpleCounter::Config>().max_size = 100;
    
    std::cout << "Intial byte counter: " << shared.get<SimpleCounter::Snapshot>().bytes << std::endl;
    
    // processing some packets
    shared.process(Packet(99));
    shared.process(Packet(100));
    shared.process(Packet(101)); // rejected because too big (max_size is set to 100)
    
    // getting the stats
    std::cout << "Byte count after processing: " << shared.get<SimpleCounter::Snapshot>().bytes << std::endl;
}

