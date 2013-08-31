#include <iostream>
#include <functional>
#include <map>
#include <string>

template<typename>
void print()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}


template<typename>
struct Signature;

template<typename R, typename T, typename ...A>
struct Signature<R(T::*)(A...)>
{
    using Ret = R;
    using Arg = std::tuple<A...>;
    static constexpr int Len = sizeof ...(A);
};


template<typename T>
std::string demangle() { return "demangle"; }


template<typename T>
T deserialize(const std::string&) { return T{}; }


template<typename T>
std::string serialize(const T&) { return "serialize"; }


std::map< std::string, std::function<std::string(const std::string&)> > mapping;



template<typename C>
struct Registrator
{
    Registrator()
    {
    }
};


#define RPC_REGISTER_COMMAND(Name) \
    namespace { Registrator<Name> gRegister##Name; }


struct Increment
{
    unsigned execute(unsigned n);
};


RPC_REGISTER_COMMAND(Increment)


int main()
{
    Signature<decltype(&Increment::execute)> sig;
    print<decltype(sig)>();
    
    using Arg = typename Signature<decltype(&Increment::execute)>::Arg;
}