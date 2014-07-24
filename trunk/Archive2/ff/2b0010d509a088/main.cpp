#include <tuple>

template<typename H, typename T>
struct typelist
{
    typedef H Head;
    typedef T Tail;
};

struct null_typelist {};

template<typename T, typename... Args>
struct tuple_push;

template<typename T, typename... Args>
struct tuple_push<T, std::tuple<Args...>>
{
    typedef std::tuple<Args..., T> type;
};

template<typename TL>
struct typelist_to_tuple;

template<typename H, typename T>
struct typelist_to_tuple<typelist<H, T>>
{
    typedef typename tuple_push<H, typename typelist_to_tuple<T>::type>::type type;
};

template<typename H>
struct typelist_to_tuple<typelist<H, null_typelist>>
{
    typedef std::tuple<H> type;
};

int main()
{
    typedef typelist<int, typelist<double, typelist<int, null_typelist>>> list;
    typedef typelist_to_tuple<list>::type tuple;
    tuple v = 1;
}