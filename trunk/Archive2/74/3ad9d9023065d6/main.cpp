#include <iostream>
#include <type_traits>

template <bool B>
struct Bool : std::integral_constant<bool, B> {};

typedef Bool<true> True;
typedef Bool<false> False;


template <typename T>
struct enable_if_t : std::enable_if<T::value, int> {};


template <typename T>
struct disable_if_t : std::enable_if<!T::value, int> {};


template <typename T>
using Invoke = typename T::type;


template <typename Condition, typename Then, typename Else>
using If = Invoke<std::conditional<Condition::value, Then, Else>>;


template <typename... T>
struct any : False {};

template <typename H, typename... T>
struct any<H, T...> : If<H, True, any<T...>>{};

template <typename... T>
using Any = Invoke<any<T...>>;


template <typename... T>
struct all : True {};

template <typename H, typename... T>
struct all<H, T...> : If<H, all<T...>, False>{};

template <typename... T>
using All = Invoke<all<T...>>;


template <typename... T>
using EnableIf = Invoke<enable_if_t<All<T...>>>;

template <typename... T>
using DisableIf = Invoke<disable_if_t<Any<T...>>>;


template <typename T, EnableIf<std::is_arithmetic<T>, std::is_scalar<T>> = 0>
void multiple_conditions(T t) {}

template <typename T, EnableIf<std::is_arithmetic<T>> = 0>
void single_condition(T t) {}

int main()
{
    multiple_conditions(int(1)); // fine

    single_condition(int(2)); // could not deduce template argument for '__formal'
}