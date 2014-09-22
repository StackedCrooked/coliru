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

template<typename T>
struct Item
{
    T item;
    
    template<typename Tuple, size_t ...I>
    Item(Tuple x, index_sequence<I...>)
        : item(get<I>(x)...)
    {}
    template<typename ...Args>
    Item(tuple<Args...> x)
        : Item(x, index_sequence_for<Args...>{})
    {}
};

template<typename T, typename ...Ts>
struct Tuple : Tuple<Ts...>, Item<T>
{
    using Item<T>::item;

    template<typename ...Args, typename ...Tail>
    Tuple(tuple<Args...> head, Tail ...tail)
        : Tuple<Ts...>(tail...), Item<T>(head)
    {}
};

template<typename T>
struct Tuple<T> : Item<T>
{
    template<typename ...Args>
    Tuple(tuple<Args...> head)
        : Item<T>(head)
    {}
};

int main()
{
    Tuple<string, Non, Non, Non> x{make_tuple(5, '*'), make_tuple(1, .1), make_tuple(2, .2), make_tuple(3, .3)};
    cout << x.item << endl;
    //auto y = move(x); - compile error
    //auto z = move(x); - compile error
}