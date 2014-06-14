#include <cstdint>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <stdexcept>
#include <boost/preprocessor/cat.hpp>
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

template<typename T>
std::string GetTypeName()
{
    static const std::string fResult = Demangle(typeid(T).name());
    return fResult;
}

template<typename T>
std::string GetTypeName(T&& t)
{
    return GetTypeName<T>();
}

template<typename T>
struct Tag
{
    friend std::string operator-(const Tag&)
    {
        return GetTypeName<T>();
    }
    
    std::pair<std::string, uint64_t> operator=(int n)
    {
        return { GetTypeName<T>(), n };
    }
};


struct num_packets : Tag<num_packets> { using Tag::operator=; } num_packets;
struct num_oversized : Tag<num_oversized> { using Tag::operator=; } num_oversized;
struct num_undersized : Tag<num_undersized> { using Tag::operator=;  } num_undersized;


struct Counters : private std::map<std::string, uint64_t>
{
    using map::map;
    using map::begin;
    using map::end;
    
    template<typename T>
    uint64_t operator[](Tag<T> t) const
    {
        auto it = find(GetTypeName<T>());
        if (it == end())
        {
            std::cout << "Not found: " << GetTypeName<T>() << std::endl;
            return uint64_t();
        }
        return it->second;
    }
    
    template<typename T>
    friend uint64_t operator/(const Counters& counters, T t)
    {
        return counters[t];
    }
    
private:
};


int main()
{
    Counters counters = {
        num_packets    = 100,
        num_oversized  = 12,
        num_undersized = 13
    };
    
    
    std::cout << counters[num_packets]     << ' '     
              << counters[num_oversized]   << ' '  
              << counters[num_undersized]  << std::endl;
    
    std::cout << counters/num_packets    << ' '     
              << counters/num_oversized  << ' '  
              << counters/num_undersized << std::endl;
}
