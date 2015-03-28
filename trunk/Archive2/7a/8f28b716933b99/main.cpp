#include <memory>
#include <iostream>
#include <stdexcept>
#include <string>
#include <map>
#include <vector>
#include <tuple>
#include <typeinfo>
#include <cxxabi.h>


std::string Demangle(char const * name)
{
    int st;
    char * const p = abi::__cxa_demangle(name, 0, 0, &st);
    switch (st)
    {
        case 0: { return std::unique_ptr<char, decltype(&std::free)>(p, &std::free).get(); }
        case -1: throw std::runtime_error("A memory allocation failure occurred.");
        case -2: throw std::runtime_error("Not a valid name under the GCC C++ ABI mangling rules.");
        case -3: throw std::runtime_error("One of the arguments is invalid.");
        default: throw std::runtime_error("unexpected demangle status");
    }
}


using Packet = std::string;


class Processor
{   
public:
    template<typename T>
    Processor(T t) : mImpl(std::make_shared<Impl<T>>(t)) {}
    
    void process(const Packet& packet)
    {
        mImpl->process(packet);
    }
    
    void print()
    {
        mImpl->print();
    }
    
private:
    struct Base
    {
        virtual void process(const Packet&) = 0;
        virtual void print() = 0;
    };
    
    template<typename T>
    struct Impl : Base
    {
        explicit Impl(T t) : t(t) {}
        
        virtual void process(const Packet& packet) 
        {
            t.process(packet);
        }
        
        virtual void print()
        {
            t.print();
        }
        
        T t;
    };
    
    std::shared_ptr<Base> mImpl;
};


struct RateCounter
{
    void process(const Packet& packet)
    {
        std::cout << "RateCounter::process: " << packet << std::endl;
        mResult.mRate++;
    }
    
    void print() const
    {
        std::cout << "RateCounter: Rate=" << mResult.mRate << std::endl;
    }
    
    struct Result
    {
        std::uint64_t mRate = 0;
    };
    
    Result getResult() const
    {
        return mResult;
    }
    
    Result mResult;
};


struct BasicCounter
{
    void process(const Packet& packet)
    {
        std::cout << "BasicCounter::process: " << packet << std::endl;
        mResult.mRxPackets++;
        mResult.mRxBytes += packet.size();
    }
    
    void print() const
    {
        std::cout << "BasicCounter: RxPackets=" << mResult.mRxPackets << " mRxBytes=" << mResult.mRxBytes << std::endl;
    }
    
    struct Result
    {
        std::uint64_t mRxPackets = 0;
        std::uint64_t mRxBytes = 0;
    };
    
    Result getResult() const
    {
        return mResult;
    }
    
    Result mResult;
};


using RemoteId = std::string;



template<typename T>
inline std::map<RemoteId, T>& GetPool()
{
    static std::map<RemoteId, T> fPool;
    return fPool;
}

template<typename T>
inline RemoteId GenerateUniqueId()
{
    static std::uint64_t fUniqueNumber;
    fUniqueNumber++;
    return Demangle(typeid(T).name()) + std::to_string(fUniqueNumber);
}

template<typename T>
inline T& GetById(RemoteId id)
{
    return GetPool<T>()[id];
}

template<typename T>
inline RemoteId CreateObject()
{
    return GenerateUniqueId<T>();
}

template<typename T>
inline T& DestroyObject(RemoteId id)
{
    auto& pool = GetPool<T>();
    auto it = pool.find(id);
    if (it == pool.end())
    {
        std::cout << "DestroyObject: object with id not found in pool: " << id << std::endl;
        return;
    }
    pool.erase(id);
}


using PortId = RemoteId;



struct BBPort
{
    template<typename T>
    void add(T t)
    {
        mProcessors.push_back(t);
    }
    
    
    std::vector<Processor> mProcessors;    
};



int main()
{
    BBPort bbPort;
    
    auto basic_counter_id = CreateObject<BasicCounter>();            
    auto rate_counter_id = CreateObject<RateCounter>();
    
    bbPort.add(GetById<BasicCounter>(basic_counter_id));
    bbPort.add(GetById<RateCounter>(rate_counter_id));
    
    auto& procs = bbPort.mProcessors;
    
    for (auto& proc : procs) proc.process("abc");
    for (auto& proc : procs) proc.process("def");
    for (auto& proc : procs) proc.print();
}
