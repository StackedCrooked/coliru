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


void deserialize(const std::string& s, int & n)
{
    n = boost::lexical_cast<int>(s);
}

template<typename T>
void deserialize(const std::string& s, std::tuple<T> & t)
{
    deserialize(s, std::get<0>(t));
}

template<typename T, typename U>
void deserialize(const std::string& s, std::tuple<T, U> & t)
{
    std::istringstream ss(s);
    ss >> std::get<0>(t);
    ss >> std::get<1>(t);
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


template<typename T, typename U>
std::string serialize(const std::tuple<T, U> & tup)
{
    return std::to_string(std::get<0>(tup)) + " " + std::to_string(std::get<1>(tup));
}


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
    static int execute(int n) { return n + 1; }
};


struct Decrement
{
    static int execute(int n) { return n - 1; }
};


struct Sum
{
    static int execute(int a, int b) { return a + b; }
};


RPC_REGISTER_COMMAND(Increment)
RPC_REGISTER_COMMAND(Decrement)
RPC_REGISTER_COMMAND(Sum)


int main()
{
    Signature<decltype(&Increment::execute)> sig;
    print<decltype(sig)>();
    
    using Arg = typename Signature<decltype(&Increment::execute)>::Arg;
    std::cout << mapping["Increment"]("100") << std::endl;
    std::cout << mapping["Decrement"]("1000") << std::endl;
    std::cout << mapping["Sum"]("3 4") << std::endl;
}