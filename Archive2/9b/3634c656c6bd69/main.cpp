#include <iostream>
#include <utility>

template<class... Ts>
struct list;

template<class A, class B>
struct merge;

template<class... As, class... Bs>
struct merge<list<As...>, list<Bs...>>
{
    using type = list<As..., Bs...>;
};

template<std::size_t N, class T>
using just = T;

template<class T, class Index>
struct repeat_impl;

template<class T, std::size_t... Ns>
struct repeat_impl<T, std::index_sequence<Ns...>>
{
    using type = list<just<Ns, T>...>;
};

template<class T, int N>
using repeat = typename repeat_impl<T, std::make_index_sequence<N>>::type;

template<class T>
struct to_list
{
    using type = list<T>;
};

template<class T, int N>
struct to_list<T[N]>
{
    using type = repeat<T, N>;
};

template<class... Ts>
struct flatten;

template<>
struct flatten<>
{
    using type = list<>;
};

template<class T, class... Ts>
struct flatten<T, Ts...>
{
    using type = typename merge<typename to_list<T>::type, typename flatten<Ts...>::type>::type;
};

struct Context
{
    template<typename T>
    T construct()
    {
        return {};
    }
};

template<class T, class List>
struct aggregate_impl;

template<class T, class... Args>
struct aggregate_impl<T, list<Args...>>
{
    static T construct(Context& ctx)
    {
        return {ctx.construct<Args>()...};
    }
};

template<class T, class... Args>
using aggregate = aggregate_impl<T, typename flatten<Args...>::type>;

struct Vector3
{
    float xyz[3];
};

int main(int argc, char** argv)
{
    using ConstructVector = aggregate<Vector3, float[3]>;
    Context ctx;
    ConstructVector::construct(ctx);
    return 0;
}