#include <cstddef>
#include <type_traits>

template<typename T>
struct identity {
    using type = T;
};

template<size_t N>
using Const = std::integral_constant<size_t, N>;

// better type list

template<typename... Args>
struct list : identity<list<Args...>> {};

using npos = std::integral_constant<size_t, static_cast<size_t>(-1)>;

template<typename List, typename A, template<typename...> class Metafunction>
struct foldl {};

template<template<typename...> class S, typename A, template<typename...> class Metafunction>
struct foldl<S<>, A, Metafunction> : identity<A> {};

template<template<typename...> class S, typename A, typename T, template<typename...> class Metafunction, typename... Args>
struct foldl<S<T, Args...>, A, Metafunction> : foldl<S<Args...>, typename Metafunction<A, T>::type, Metafunction> {};

template<typename List, template<typename...> class Metafunction>
struct maximum;

template<template<typename...> class S, typename T, template<typename...> class Metafunction>
struct maximum<S<T>, Metafunction> : Const<Metafunction<T>::value> {};

template<template<typename...> class S, template<typename...> class Metafunction, typename T, typename... Args>
struct maximum<S<T, Args...>, Metafunction> :
    Const<(Metafunction<T>::value > maximum<S<Args...>, Metafunction>::value ?
           Metafunction<T>::value : maximum<S<Args...>, Metafunction>::value)> {};

template<typename List, template<typename...> class Metafunction>
struct minimum;

template<template<typename...> class S, typename T, template<typename...> class Metafunction>
struct minimum<S<T>, Metafunction> : Const<Metafunction<T>::value> {};

template<template<typename...> class S, template<typename...> class Metafunction, typename T, typename... Args>
struct minimum<S<T, Args...>, Metafunction> :
    Const<(Metafunction<T>::value < minimum<S<Args...>, Metafunction>::value ?
           Metafunction<T>::value : minimum<S<Args...>, Metafunction>::value)> {};

template<typename List>
struct empty;

template<template<typename...> class S, typename... Args>
struct empty<S<Args...>> : std::integral_constant<bool, sizeof...(Args) == 0> {};

template<typename List>
struct size;

template<template<typename...> class S, typename... Args>
struct size<S<Args...>> : Const<sizeof...(Args)> {};

template<typename List>
struct front {};

template<template<typename...> class S, typename T, typename... Args>
struct front<S<T, Args...>> : identity<T> {};

template<typename List>
struct back {};

template<template<typename...> class S, typename T, typename... Args>
struct back<S<T, Args...>> : identity<typename back<S<Args...>>::type> {};

template<template<typename...> class S, typename T>
struct back<S<T>> : identity<T> {};

template<typename List>
struct clear {};

template<template<typename...> class S, typename... Args>
struct clear<S<Args...>> : identity<S<>> {};

template<typename List, typename T>
struct push_back {};

template<template<typename...> class S, typename... Args, typename T>
struct push_back<S<Args...>, T> : identity<S<Args..., T>> {};

template<typename List, typename T>
struct push_front {};

template<template<typename...> class S, typename... Args, typename T>
struct push_front<S<Args...>, T> : identity<S<T, Args...>> {};

template<typename List>
struct pop_back {};

template<template<typename...> class S>
struct pop_back<S<>> : identity<S<>> {};

template<template<typename...> class S, typename T>
struct pop_back<S<T>> : identity<S<T>> {};

template<template<typename...> class S, typename T, typename... Args>
struct pop_back<S<T, Args...>> : identity<typename push_front<typename pop_back<S<Args...>>::type, T>::type> {};

template<typename List>
struct pop_front {};

template<template<typename...> class S>
struct pop_front<S<>> : identity<S<>> {};

template<template<typename...> class S, typename T, typename... Args>
struct pop_front<S<T, Args...>> : identity<S<Args...>> {};

template<typename List, template<typename...> class Metafunction>
struct map {};

template<template<typename...> class S, template<typename...> class Metafunction>
struct map<S<>, Metafunction> : identity<S<>> {};

template<template<typename...> class S, typename... Args, template<typename...> class Metafunction>
struct map<S<Args...>, Metafunction> : identity<S<typename Metafunction<Args>::type...>> {};

template<typename List, size_t N>
struct at {};

template<template<typename...> class S, typename T, typename... Args, size_t N>
struct at<S<T, Args...>, N> : at<S<Args...>, N - 1> {};

template<template<typename...> class S, typename T, typename... Args>
struct at<S<T, Args...>, 0> : identity<T> {};

template<typename Left, typename Right>
struct join {};

template<template<typename...> class S, typename... A, typename... B>
struct join<S<A...>, S<B...>> : identity<S<A..., B...>> {};

template<typename List, typename T>
struct has_type;

template<template<typename...> class S, typename T>
struct has_type<S<>, T> : std::false_type {};

template<template<typename...> class S, typename T, typename U, typename... Args>
struct has_type<S<U, Args...>, T> : has_type<S<Args...>, T> {};

template<template<typename...> class S, typename T, typename... Args>
struct has_type<S<T, Args...>, T> : std::true_type {};

int main() {
    using x = list<int, float, char, double, long double>;
    using y = std::common_type<int, int, float, char, double, long double>::type;
    static_assert(maximum<x, std::alignment_of>::value == alignof(long double), "...");
    static_assert(minimum<x, std::alignment_of>::value == alignof(char), "...");
    static_assert(has_type<x, int>::value, "...");
    static_assert(std::is_same<foldl<x, int, std::common_type>::type, y>::value, "...");
    static_assert(std::is_same<back<x>::type, long double>::value, "...");
    static_assert(std::is_same<at<x, 3>::type, double>::value, "...");
    static_assert(empty<x>::value == false, "...");
}
