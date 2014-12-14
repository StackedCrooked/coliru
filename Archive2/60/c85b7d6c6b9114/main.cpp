#include <iostream>
#include <cxxabi.h>
#include <string>
#include <memory>

template <typename T>
std::string demangle() {
    std::unique_ptr<char, decltype(&std::free)> result{
        abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, nullptr),
        std::free
    };
    
    return result.get();
}

template <typename T, typename F>
using apply_t = decltype(std::declval<F>()(std::declval<T>()));

template <typename... Rest>
struct Tuple 
{ 
    template <typename F>
    Tuple<> Transform(F )
    { 
        return {};
    }
};

template <typename First, typename... Rest>
struct Tuple<First, Rest...>
{
    Tuple(First f, Rest... r)
    : first(f), rest(r...)
    { }
    
    Tuple(First f, const Tuple<Rest...>& tup_r)
    : first(f), rest(tup_r)
    { }
    
    template <typename F>
    Tuple<apply_t<First, F>, apply_t<Rest, F>...>
    Transform(F func)
    {
        return {func(first), rest.Transform(func)};
    }
    
    First first;
    Tuple<Rest...> rest;
};

struct Zero
{
    template <typename T>
    int operator()(T ) { return 0; }
};

struct Incr
{
    template <typename T>
    T operator()(T x) { return x + 1; }
};

int main() {
    Tuple<int, double, char> t(1, 2.0, 'c');   
    std::cout << demangle<decltype(t)>() << std::endl;
    
    auto z = t.Transform(Zero{});
    std::cout << demangle<decltype(z)>() << std::endl;
    std::cout << z.first << std::endl;
    
    auto i = t.Transform(Incr{});
    std::cout << demangle<decltype(i)>() << std::endl;
    std::cout << i.rest.first << std::endl;    
}