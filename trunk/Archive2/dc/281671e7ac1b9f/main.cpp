#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/apply.hpp>
#include <iostream>
#include <array>
#include <utility>
#include <cstddef>

namespace mpl = boost::mpl;

template <std::size_t...> struct index_sequence {};
template <std::size_t N, std::size_t... Is> struct make_index_sequence : make_index_sequence<N-1, N-1, Is...> {};
template <std::size_t... Is> struct make_index_sequence<0, Is...> : index_sequence<Is...> {};

template <typename OP, typename T, typename E, std::size_t N, std::size_t... Is>
auto apply(std::array<E, N>& args, index_sequence<Is...>)
    -> decltype(typename mpl::apply<OP, T>::type()(args[Is]...))
{
    return typename mpl::apply<OP, T>::type()(args[Is]...);
}

template <typename OP, typename T, typename E, std::size_t N>
auto apply(std::array<E, N>& args)
    -> decltype(apply<OP, T>(args, make_index_sequence<N>{}))
{
    return apply<OP, T>(args, make_index_sequence<N>{});
}

int main()
{
    using OP = std::plus<mpl::_>;
    std::array<int, 2> args = {1, 2};

    auto n1 = mpl::apply<OP, int>::type()(args[0], args[1]);

    std::cout << "plus (1,2) = " << n1 << std::endl;
    
    auto n2 = apply<OP, int>(args);
    
    std::cout << "plus (1,2) = " << n2 << std::endl;
}
