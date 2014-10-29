#include <tuple>
#include <type_traits>

template<template<class...> class Template, std::size_t N, class T>
struct BindN {
    template<std::size_t> struct DelayedFalse : std::false_type {};
    template<std::size_t I, class, class>
    struct BindNHelper {
        // we have to use DelayedFalse to static_assert on instantiation
        static_assert(DelayedFalse<I>::value, "BindN index too high");
    };
    
    template<std::size_t I, class ...Head, class Mid, class ...Tail>
    struct BindNHelper<I, std::tuple<Head...>, std::tuple<Mid, Tail...>> 
    : BindNHelper<I - 1, std::tuple<Head..., Mid>, std::tuple<Tail...>> { };
    
    template<class ...Head, class Mid, class ...Tail>
    struct BindNHelper<0, std::tuple<Head...>, std::tuple<Mid, Tail...>> {
        using type = Template<Head..., T, Mid, Tail...>;
    };
    
    template<class ...Head>
    struct BindNHelper<0, std::tuple<Head...>, std::tuple<>> {
        using type = Template<Head..., T>;
    };
    
    template<class ...U>
    using type = typename BindNHelper<N, std::tuple<>, std::tuple<U...>>::type;
};

#define BINDN(Template, N, T) BindN<Template, N, T>::template type


int main(int argc, char** argv) {
    BINDN(std::tuple, 2, const char*)<int, double, int> x { 2, 5.6, "test", 2 };
    
    return 0;
}
