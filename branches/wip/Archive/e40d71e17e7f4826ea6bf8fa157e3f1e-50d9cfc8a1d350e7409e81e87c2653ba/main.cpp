#include <cstring>
#include <iostream>
#include <memory>
#include <typeinfo>
#include <cxxabi.h>


std::string Demangle(const char * name)
{
    int st;
    char * const p = abi::__cxa_demangle(name, 0, 0, &st);
    switch (st)
    {
        case  0: return std::unique_ptr<char, decltype(&std::free)>(p, &std::free).get();
        case -1: throw std::runtime_error("A memory allocation failure occurred.");
        case -2: throw std::runtime_error("Not a valid name under the GCC C++ ABI mangling rules.");
        case -3: throw std::runtime_error("One of the arguments is invalid.");
        default: throw std::runtime_error("Unexpected demangle status");
    }
}


template<typename T>
const std::string& GetTypeName()
{
    static std::string name = Demangle(typeid(T).name());
    return name;
}

int main()
{
    std::cout << GetTypeName<int>() << std::endl;
}