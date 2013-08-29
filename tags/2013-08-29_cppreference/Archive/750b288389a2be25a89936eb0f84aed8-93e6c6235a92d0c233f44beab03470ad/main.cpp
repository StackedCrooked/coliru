#include <type_traits>
#include <algorithm>

/* Helpers */
template<typename T>
using Type = typename T::type;

template<typename T>
using Unqualified = Type<std::remove_reference<Type<std::remove_cv<T>>>>;

template<typename Specialization, typename Target>
struct rebind {};

/* Sensible default: assume first parameter is for the target */
template<template<typename...> class Cont, typename T, typename... Ts, typename Target>
struct rebind<Cont<T, Ts...>, Target> {
    using type = Cont<Target, Ts...>;
};

/* Special-case */
template<typename Old, std::size_t N, typename Target>
struct rebind<std::array<Old, N>, Target> {
    using type = std::array<Target, N>;
};

template<typename Specialization, typename Target>
using Rebind = Type<rebind<Specialization, Target>>;

#include <tuple>

template<typename T>
struct function_traits : public function_traits<decltype(&T::operator())> {};

template<typename T, typename R, typename... Args>
struct function_traits<R(T::*)(Args...) const> {
    
    static constexpr size_t args = sizeof...(Args);

    using result_type = R;
    template<size_t i>
    struct arg {
        using type = typename std::tuple_element<i,std::tuple<Args...>>::type;
    };
};

template<typename T>
using Resultant = typename function_traits<T>::result_type;

template<typename T>
using ResultOf = Type<std::result_of<T>>;

template<class Cont, typename Map>
auto map(const Cont& cont, Map&& mapped) -> Rebind<Cont, ResultOf<Unqualified<Map>>> {
    Rebind<Cont, ResultOf<Unqualified<Map>>> result;
    auto result_iterator = std::back_inserter(result);
    for(const auto& elem : cont) {
        *result_iterator = mapped(elem);
    }
    return result;
}

#include <iostream>

int main() {
    auto i = map(std::vector<int>{1,2,3,4,5,6}, [](int x) { return x % 2 == 0; });
    for(auto&& j : i) {
        std::cout << j << ' ';
    }
}