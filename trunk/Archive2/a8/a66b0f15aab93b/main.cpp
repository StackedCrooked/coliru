#include <array>
#include <vector>
#include <tuple>
#include <iostream>

template <typename T, typename U = void>
struct is_tuple_like : std::false_type {};

template <typename T>
struct is_tuple_like<T, decltype(std::get<0>(std::declval<T>()), void())> : std::true_type {};

// 1
template <typename T, std::enable_if_t<!is_tuple_like<std::decay_t<T>>::value, int> = 0>
void func(T&& t)
{
    std::cout << 1 << std::endl;
}

// 2
template <typename TupleType, std::enable_if_t<is_tuple_like<std::decay_t<TupleType>>::value, int> = 0>
void func(TupleType&& tup)
{
    std::cout << 2 << std::endl;
}

int main()
{
    int i;
    std::vector<int> v;
    auto t = std::make_tuple(1, 2.0, 'a');
    auto p = std::make_tuple(1, 2.0);

    func(i); // calls 1
    func(v); // calls 1

    func(t); // calls 2
    func(p); // calls 2
}
