#include <array>
#include <vector>
#include <tuple>
#include <iostream>
#include <utility>
#include <type_traits>

template <typename T, typename U = void>
struct is_tuple_like : std::false_type {};

template <typename T>
struct is_tuple_like<T, decltype(std::get<0>(std::declval<T>()), std::tuple_size<T>::value, void())> : std::true_type {};

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
    std::array<int, 5> a;
    std::vector<int> v;
    std::pair<char, float> p;
    auto t1 = std::make_tuple(1, 2.0, 'a');
    auto t2 = std::make_tuple(1, 2.0);

    func(i); // calls 1
    func(v); // calls 1

    func(t1); // calls 2
    func(t2); // calls 2
    func(p); // calls 2
    func(a); // calls 2
}
