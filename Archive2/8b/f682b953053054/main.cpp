#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/apply.hpp>
#include <iostream>
#include <array>
#include <utility>

template <typename Func, typename T, size_t N, size_t... Inds>
int ApplyFuncHelper(std::array<T, N> const& arr, std::index_sequence<Inds...>)
{
 return Func()(std::get<Inds, T, N>(arr)...);
}

template <typename Func, typename T, size_t N>
int ApplyFunc(std::array<T, N> const& arr)
{
 return ApplyFuncHelper<Func>(arr, std::make_index_sequence<N>());
}

namespace mpl = boost::mpl;

int main() {
    using OP = std::plus<mpl::_>;
    std::array<int, 2> args = {{1, 2}};

    // This works (passing each arg separately)
    auto n1 = mpl::apply<OP, int>::type()(args[0], args[1]);

    std::cout << "plus (1,2) = " << n1 << std::endl;

    auto n2 = ApplyFunc<mpl::apply<OP, int>::type>(args);
    std::cout << "plus (1,2) = " << n2 << std::endl;
    
    return 0;
}