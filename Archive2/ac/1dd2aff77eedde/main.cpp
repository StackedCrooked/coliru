#include <boost/tuple/tuple_io.hpp>
#include <iostream>

using boost::tuple;
using boost::make_tuple;

template <int... denomination>
    static constexpr auto change(int amount) -> decltype(make_tuple(denomination...))
    {
        typedef decltype(make_tuple(denomination...)) R;
        return R { [&]() { auto fill=amount/denomination; amount-=denomination*fill; return fill;}()... };
    }

int main() {
    auto coins = change<100,50,20,10,5,1>(367);
    std::cout << coins;
}