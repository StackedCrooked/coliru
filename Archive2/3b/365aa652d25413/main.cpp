#include <tuple>
#include <iostream>

template <signed int element, class Fun, class... TupleArgs, class... ParamArgs>
typename std::enable_if<(element == -1)>::type call_impl(Fun function, std::tuple<TupleArgs...>, ParamArgs... args)
{
    function(args...);
}

template <signed int element, class Fun, class... TupleArgs, class... ParamArgs>
typename std::enable_if<(element != -1)>::type call_impl(Fun function, std::tuple<TupleArgs...> tup, ParamArgs... args)
{
    call_impl<element - 1>(function, tup, std::get<element>(tup), args...);
}

template <class Fun, class... TupleArgs>
void call(Fun function, std::tuple<TupleArgs...> tup)
{
    call_impl<std::tuple_size<std::tuple<TupleArgs...> >::value - 1>(function, tup);    
}

void doThing(int x, int y)
{
    std::cout << x << " " << y << std::endl;
}
int main()
{
    auto tup = std::make_tuple(5, 1);
    call(&doThing, tup);
    return 0;
}