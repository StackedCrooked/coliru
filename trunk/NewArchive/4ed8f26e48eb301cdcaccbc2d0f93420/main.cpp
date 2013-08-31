#include <boost/lexical_cast.hpp>
#include <iostream>
#include <functional>
#include <map>
#include <sstream>
#include <string>
#include <tuple>
template<typename>


void print()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}


template<typename>
struct Signature;

template<typename R, typename ...A>
struct Signature<R(*)(A...)>
{
    using Ret = R;
    using Arg = std::tuple<A...>;
    static constexpr int Len = sizeof ...(A);
};


template<typename T>
std::string demangle() { return "demangle"; }


void deserialize(const std::string& s, unsigned & n)
{
    n = boost::lexical_cast<unsigned>(s);
}

template<typename T>
void deserialize(const std::string& s, std::tuple<T> & t)
{
    deserialize(s, std::get<0>(t));
}

template<typename T>
T deserialize(const std::string& s)
{
    T t;
    deserialize(s, t);
    return t;
}


template<typename T>
std::string serialize(const T& t) { return std::to_string(t); }


std::map< std::string, std::function<std::string(const std::string&)> > mapping;
    

template<typename C>
class Registrator {
    
    template<int ...> struct seq { };
    
    template<int N, int ...S>
    struct gens : gens<N-1, N-1, S...> { };
    
    template<int ...S>
    struct gens<0, S...> { typedef seq<S...> type; };

    template<typename Arg, int ...S>
    static auto invoke_impl(const Arg & arg, seq<S...>) -> decltype(C::execute(std::get<S>(arg)...))
    {
        return C::execute(std::get<S>(arg)...);
    }

    template<typename ...Args>
    static auto invoke(const std::tuple<Args...> & arg) -> decltype(invoke_impl(arg, typename gens<sizeof...(Args)>::type()))
    {
        return invoke_impl(arg, typename gens<sizeof...(Args)>::type());
    }

public:
    Registrator(const std::string & inName)
    {
        mapping.insert(std::make_pair(inName, [this](const std::string & str) -> std::string {
            return serialize(this->invoke(deserialize<typename Signature<decltype(&C::execute)>::Arg>(str)));
        }));
    }
};


#define RPC_REGISTER_COMMAND(Name) \
    namespace { Registrator<Name> gRegister##Name(#Name); }


struct Increment
{
    static unsigned execute(unsigned n) { return n + 1; }
};


struct Decrement
{
    static unsigned execute(unsigned n) { return n - 1; }
};


RPC_REGISTER_COMMAND(Increment)
RPC_REGISTER_COMMAND(Decrement)


int main()
{
    Signature<decltype(&Increment::execute)> sig;
    print<decltype(sig)>();
    
    using Arg = typename Signature<decltype(&Increment::execute)>::Arg;
    std::cout << mapping["Increment"]("100") << std::endl;
    std::cout << mapping["Decrement"]("999") << std::endl;
}