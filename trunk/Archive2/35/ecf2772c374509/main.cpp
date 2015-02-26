#include <array>
#include <vector>
#include <tuple>
#include <iostream>
#include <utility>
#include <type_traits>

template <typename T, typename U = void>
struct is_tuple_like : std::false_type {};

template <typename T>
struct is_tuple_like<T, decltype((void)std::get<0>(std::declval<T>()), (void)std::tuple_size<T>::value)> : std::true_type {};

struct A {};
struct B {};

// 1
template <typename T>
A _func(T&& t, std::false_type)
{
    std::cout << 1 << std::endl;
    return {};
}

// 2
template <typename TupleType>
B _func(TupleType&& tup, std::true_type)
{
    std::cout << 2 << std::endl;
    return {};
}

template <typename TupleOrNot>
auto func(TupleOrNot&& t)
{
    return _func(std::forward<TupleOrNot>(t), is_tuple_like<std::decay_t<TupleOrNot>>{});
}

int main()
{
    int i;
    std::array<int, 5> ar;
    std::vector<int> v;
    std::pair<char, float> p;
    auto t1 = std::make_tuple(1, 2.0, 'a');
    auto t2 = std::make_tuple(1, 2.0);

    A a1 = func(i); // calls 1
    A a2 = func(v); // calls 1

    B b1 = func(t1); // calls 2
    B b2 = func(t2); // calls 2
    B b3 = func(p); // calls 2
    B b4 = func(ar); // calls 2
}