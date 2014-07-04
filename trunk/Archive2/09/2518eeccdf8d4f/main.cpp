#include <iostream>
#include <string>
#include <vector>
#include <tuple>

template<size_t... Args>
struct index_seq {};

template<size_t CurInd, size_t... Indexes>
struct make_index_seq_helper
{
    typedef typename make_index_seq_helper<CurInd-1, CurInd-1, Indexes...>::type type;
};

template<size_t... Indexes>
struct make_index_seq_helper<0, Indexes...>
{
    typedef index_seq<Indexes...> type;
};

template<size_t Size>
using make_index_seq = typename make_index_seq_helper<Size>::type;

template<typename F, typename Tuple, size_t... Seq>
auto call_impl(F f, Tuple t, index_seq<Seq...>)
{
    return f(std::get<Seq>(t)...);
}

template<typename F, typename... Args>
auto call(F f, std::tuple<Args...> t)
{
    return call_impl(f, t, make_index_seq<sizeof...(Args)>{});
}

void foo(int i, double j)
{
    std::cout << i << " " << j;
}

int main()
{
    auto t = std::make_tuple(1, 2.0);
    call(foo, t);
}
