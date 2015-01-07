#include <iostream>
#include <typeinfo>
#include <cxxabi.h>
#include <string>

template <typename ...Ts> struct type_list;
template <typename T1, typename T2> struct pair;

namespace detail {

// print scalar types
template <typename T>
struct type_printer {
    std::string operator()() const {
        int s;
        return abi::__cxa_demangle(typeid(T).name(), 0, 0, &s);
    }   
};

// print pair<T, U> types
template <typename T, typename U>
struct type_printer<pair<T, U>> {
    std::string operator()() const {
        return "(" + type_printer<T>()() + "," + type_printer<U>()() + ")";
    }   
};

// print type_list<T>
template <>
struct type_printer<type_list<>> {
    std::string operator()() const {
        return "\u2205";
    }   
};

template <typename T>
struct type_printer<type_list<T>> {
    std::string operator()() const {
        return "{" + type_printer<T>()() + "}";
    }   
    std::string operator()(const std::string& sep) const {
        return sep + type_printer<T>()();
    }   
};

template <typename T, typename ...Ts>
struct type_printer<type_list<T, Ts...>> {
    std::string operator()() const {
        return "{" + type_printer<T>()() + type_printer<type_list<Ts...>>()(std::string(", ")) + "}";
    }   
    std::string operator()(const std::string& sep) const {
        return sep + type_printer<T>()() + type_printer<type_list<Ts...>>()(sep);
    }   
};
}



template <typename T>
std::string print_type()
{
    return detail::type_printer<T>()();
}




template<typename ...Ts> struct type_list {};
template<typename T1, typename T2> struct pair {};

// Concatenation
template <typename ... T> struct concat;
template <typename ... Ts, typename ... Us>
struct concat<type_list<Ts...>, type_list<Us...>>
{
    typedef type_list<Ts..., Us...> type;
};

// Cross Product
template <typename T, typename U> struct cross_product;

// Partially specialise the empty case for the first type_list.
template <typename ...Us>
struct cross_product<type_list<>, type_list<Us...>> {
    typedef type_list<> type;
};

// The general case for two type_lists. Process:
// 1. Expand out the head of the first type_list with the full second type_list.
// 2. Recurse the tail of the first type_list.
// 3. Concatenate the two type_lists.
template <typename T, typename ...Ts, typename ...Us>
struct cross_product<type_list<T, Ts...>, type_list<Us...>> {
    typedef typename concat<
        type_list<pair<T, Us>...>,
        typename cross_product<type_list<Ts...>, type_list<Us...>>::type
    >::type type;
};
template <typename T, typename U>
void test()
{
    std::cout << print_type<T>() << " \u2a2f " << print_type<U>() << " = "
        << print_type<typename cross_product<T, U>::type>() << std::endl;
}

struct _{};
struct Eth{};
struct PPPoE{};
struct VLAN{};
struct L2TPv3{};
struct IPv4{};
struct IPv6{};
struct TCP{};
struct UDP{};


template<typename ...>
struct Path;


template<typename ...L25, typename ...L35>
struct Path<type_list<L25...>, type_list<L35...>>
{   
    using type = typename cross_product<
        typename cross_product<
            typename cross_product<
                typename cross_product<
                    type_list<Eth>,
                    type_list<L25...>
                >::type,
                type_list<IPv4, IPv6>
            >::type,
            type_list<L35...>
        >::type,
        type_list<TCP, UDP>
    >::type;
};
    
    
int main()
{
    std::cout << print_type<Path<type_list<_, VLAN, PPPoE>, type_list<_, L2TPv3>>::type>() << std::endl;
    return 0;
}

