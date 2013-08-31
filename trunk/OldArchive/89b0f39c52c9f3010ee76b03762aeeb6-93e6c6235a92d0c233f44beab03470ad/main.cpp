#include <iterator>
#include <type_traits>
#include <utility>

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

template<typename Specialization, typename Target>
using Rebind = typename rebind<Specialization, Target>::type;

template<typename T>
struct result_of_impl : public result_of_impl<decltype(&T::operator())> {};

template<typename T, typename R, typename... Args>
struct result_of_impl<R(T::*)(Args...) const> {
    using type = R;
};

template<typename T, typename R, typename... Args>
struct result_of_impl<R(T::*)(Args...)> {
    using type = R;
};

template<typename T>
using ResultOf = Type<result_of_impl<T>>;

template<class Container>
struct LINQ_Object {
private:
    Unqualified<Container> cont;
public:
    LINQ_Object(Container&& container): cont(std::forward<Container>(container)) {}
    template<class Predicate>
    auto where(Predicate&& pred) -> decltype(*this) {
        auto first = std::begin(std::forward<Container>(cont));
        auto last = std::end(std::forward<Container>(cont));
        auto result = first;
        for(; first != last; ++first) {
            if(pred(*first))
                *result++ = *first;
        }
        cont.erase(result, last);
        return *this;
    }

    Container select() {
        return cont;
    }

    template<typename Map>
    auto select(Map&& mapper) -> Rebind<Unqualified<Container>, ResultOf<Unqualified<Map>>> {
        Rebind<Unqualified<Container>, ResultOf<Unqualified<Map>>> result;
        auto inserter = std::back_inserter(result);
        for(const auto& elem : cont) {
            *inserter++ = mapper(elem);
        }
        return result;
    }
};

template<class Container>
LINQ_Object<Container> from(Container&& cont) {
    return LINQ_Object<Container>(std::forward<Container>(cont));
}


#include <iostream>
#include <vector>

int main() {
    std::vector<int> v = {1,2,3,4,5,6,7,8,9,10};
    auto lol = from(v).where([](int x) { return x > 5; }).select([](int x) { return x + 1; });
    for(auto&& i : lol) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
    for(auto&& j : v) {
        std::cout << j << ' ';
    }
}