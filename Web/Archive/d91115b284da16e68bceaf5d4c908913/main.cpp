#include <cassert>
#include <cstdlib>
#include <cxxabi.h>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <typeinfo>


std::string demangle(const char * name)
{
    int st;
    std::shared_ptr<char> p(abi::__cxa_demangle(name, 0, 0, &st), std::free);
    if (st != 0)
    {
        switch (st)
        {
            case -1: throw std::runtime_error("A memory allocation failure occurred.");
            case -2: throw std::runtime_error("Not a valid name under the GCC C++ ABI mangling rules.");
            case -3: throw std::runtime_error("One of the arguments is invalid.");
            default: throw std::runtime_error("Unexpected demangle status");
        }
    }
    return std::string(p.get());
}



template<typename SubType>
struct Enum {};

template<typename E, typename e, unsigned Index>
struct Enumerator
{
    using enum_type = E;
    using enumerator_type = e;
    static constexpr unsigned index = Index;
    static constexpr bool end = (Index == ~0u);
};

template<typename E, typename e, unsigned N>
std::ostream& operator<<(std::ostream& os, Enumerator<E, e, N>)
{
    return os << demangle(typeid(e).name());
}

struct RGB : Enum<RGB>
{
    struct Red   : Enumerator<RGB, Red  , 0u> {};
    struct Green : Enumerator<RGB, Green, 1u> {};
    struct Blue  : Enumerator<RGB, Blue , 2u> {};
    
    static constexpr Red   red   {};
    static constexpr Green green {};
    static constexpr Blue  blue  {};
};


int main()
{
    std::cout << RGB::red   << std::endl;
    std::cout << RGB::green << std::endl;
    std::cout << RGB::blue  << std::endl;
}