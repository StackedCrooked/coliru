#include <iostream>
#include <type_traits>


    template<typename... Ts>
    struct make_void { typedef void type;};
    
    template<typename... Ts>
    using void_t = typename make_void<Ts...>::type;

template <typename T>
struct IsMyType : std::false_type{};

template <> struct IsMyType<double> : std::true_type{};

template <typename T>
typename std::enable_if<IsMyType<T>::value, std::ostream &>::type
Print(std::ostream &o, T const & t)
{
    o << t;
    return o;
}

template<typename T, typename = void>
struct CanCallPrint : std::false_type
{
};

template<typename T>
struct CanCallPrint<T, void_t<decltype(Print(std::cout,std::declval<T&>()))>> : std::true_type
{
};

static_assert(CanCallPrint<double>::value,"boom");


int main()
{
    
}