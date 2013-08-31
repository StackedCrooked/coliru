#include <tuple>

template<int I, typename Tuple>
typename std::tuple_element<I, Tuple>::type foo(Tuple& tuple)
{
    using std::get;
    return get<I>(tuple);
}

struct lol {};

template<int I, typename T>
lol foo(T const&, ...)
{ return {}; }

int main()
{
    lol l = foo<0>(42);
    (void)l;
}