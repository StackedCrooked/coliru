#include <iostream>
#include <cstddef>
#include <utility>
#include <string>
#include <tuple>
using namespace std;

struct Non
{
    Non(int x, double y)
    {
        cout << x << " " << y << endl;
    }
    Non(const Non&) = delete;
    Non(Non&&) = delete;
    Non &operator=(const Non&) = delete;
    Non &operator=(Non&&) = delete;
};

template<typename T, typename ...Ts>
struct test : test<Ts...>
{
    using base = test<Ts...>;
    T item;

    template<typename Head, size_t ...I, typename ...Tail>
    test(index_sequence<I...>, Head head, Tail ...tail)
        : base(tail...), item(get<I>(head)...)
    {}
    template<typename ...Args, typename ...Tail>
    test(tuple<Args...> head, Tail ...tail)
        : test(index_sequence_for<Args...>{}, head, tail...)
    {}
};

template<typename T>
struct test<T>
{
    T item;

    template<typename Head, size_t ...I>
    test(index_sequence<I...>, Head head)
        : item(get<I>(head)...)
    {}
    template<typename ...Args>
    test(tuple<Args...> head)
        : test(index_sequence_for<Args...>{}, head)
    {}
};

int main()
{
    test<string, Non, Non, Non> x{make_tuple(5, '*'), make_tuple(1, .1), make_tuple(2, .2), make_tuple(3, .3)};
    cout << x.item << endl;
    //auto y = move(x); - compile error
    //auto z = move(x); - compile error
}