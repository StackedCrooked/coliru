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
// Refcounted pointers will help to prevent lifetime issues because of the async
// processing.
//
// This class also provides the virtual method dispatch to the (static) processors.
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
            // NOTE: swith to dynamic_cast if this turns out to be too error-prone.
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
    using Processor = struct SimpleCounter;

    struct Config
    {
        int min_size = 60;
        int max_size = 1500;
    };

    struct Snapshot
    {
        int packets = 0;
        int bytes = 0;
        int badsize[2] = {}; // "undersize" and "oversized"
    };
};


// SimpleCounter class' only responsibility is the actual packet counting.
// 
// Usage is similar to calling a function:
//   SimpleCounter(config, snapshot).process(packet);
//
// The config and stats objects are only stored by ref here.
// Their real storage location is decided by higher level code.
// This allows us to store them in a pool optimized for data locality
// or in a pool that helps to prevent false sharing, etc..
// (Currently they are stored inside SharedProcessor).
struct SimpleCounter : SimpleCounterTraits
{
    SimpleCounter(const Config& config, Snapshot& snapshot) : config(config), snapshot(snapshot) {}

    void process(const Packet& packet) const && // (experimental: ref-qualifier enforces the function-like calling style. probably useless)
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

    void process(const PacketGroup& group) const &&
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

    // Config and stats stored by ref here.
    // I wonder if it could be more optimal to store by value here.
    const Config& config;
    Snapshot& snapshot;
};


int main()
{
    SharedProcessor shared(SimpleCounterTraits{});
    
    // update the config
    shared.get<SimpleCounter::Config>().max_size = 100;

    // print intial stats
    std::cout << "Intial byte counter: " << shared.get<SimpleCounter::Snapshot>().bytes << std::endl;
    
    // process some packets
    shared.process(Packet(99));
    shared.process(Packet(100));
    shared.process(Packet(101)); // rejected because too big (max_size is set to 100)
    
    // print new stats
    std::cout << "Byte count after processing: " << shared.get<SimpleCounter::Snapshot>().bytes << std::endl;
}

