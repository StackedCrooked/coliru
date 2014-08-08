#include <exception>
#include <iostream>
#include <memory>
#include <stdexcept>
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


struct baby_jeebus {};


int main()
{
    
    try
    {
        throw baby_jeebus {};
    }
    catch (...)
    {
        std::cout << "Caught " << Demangle(abi::__cxa_current_exception_type()->name()) << std::endl;
    }
}
