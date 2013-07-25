#include <iterator>
#include <type_traits>
#include <utility>

template<typename T>
using Type = typename T::type;

template<typename T>
using RemoveCV = Type<std::remove_cv<T>>;

template<typename T>
using Unqualified = Type<std::remove_reference<RemoveCV<T>>>;

template<typename Specialization, typename Target>
struct rebind {};

/* Sensible default: assume first parameter is for the target */
template<template<typename...> class Cont, typename T, typename... Ts, typename Target>
struct rebind<Cont<T, Ts...>, Target> {
    using type = Cont<Target, Ts...>;
};

// /* Special-case */
// template<typename Old, std::size_t N, typename Target>
// struct rebind<std::array<Old, N>, Target> {
//     using type = std::array<Target, N>;
// };

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

template<class Container, class T = Unqualified<Container>>
struct LINQ_Object {
private:
    T cont;
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

    auto take(size_t n) -> decltype(*this) {
        size_t size = cont.size();
        for(unsigned i = n; i < size; ++i)
            cont.pop_back();
        return *this;
    }

    template<class Predicate>
    auto takeWhile(Predicate&& pred) -> decltype(*this) {
        auto first = std::begin(std::forward<Container>(cont));
        auto last = std::end(std::forward<Container>(cont));
        for(; first != last; ++first) {
            if(!pred(*first))
                break;
        }
        cont.erase(first, last);
        return *this;
    }

    auto skip(size_t n) -> decltype(*this) {
        auto last = std::begin(std::forward<Container>(cont)) + n;
        auto first = std::begin(std::forward<Container>(cont));
        cont.erase(first, last);
        return *this;
    }

    // if true, increment, if false, return remainder
    template<class Predicate>
    auto skipWhile(Predicate&& pred) -> decltype(*this) {
        auto first = std::begin(std::forward<Container>(cont));
        auto result = first;
        auto last = std::end(std::forward<Container>(cont));
        for(; first != last; ++first) {
            if(pred(*first))
                ++result;
            else
                break;
        }
        cont.erase(std::begin(std::forward<Container>(cont)), result);
        return *this;
    }

    operator T() {
        return cont;
    }

    T select() {
        return cont;
    }

    template<typename Map>
    auto select(Map&& mapper) -> Rebind<T, ResultOf<Unqualified<Map>>> {
        Rebind<T, ResultOf<Unqualified<Map>>> result;
        auto inserter = std::back_inserter(result);
        for(const auto& elem : cont) {
            *inserter++ = mapper(elem);
        }
        return result;
    }
};

template<class Container>
LINQ_Object<Container> from(Container&& cont) {
    return { std::forward<Container>(cont) };
}

#include <iostream>
#include <vector>

int main() {
    std::vector<int> v = {5, 4, 1, 3, 9, 8, 6, 7, 2, 0};
    auto lol = from(v).skipWhile([](int x) { return x % 3 != 0; }).select();
    for(auto&& i : lol) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
    for(auto&& j : v) {
        std::cout << j << ' ';
    }
}