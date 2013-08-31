#include <cstddef>
using std::size_t;

template < typename T
         , size_t Size >
struct array
{
    T buf[Size];

    constexpr size_t size() const { return Size; }
};

namespace detail{
template <std::size_t... Is>
struct indices {};

template <std::size_t N, std::size_t... Is>
struct build_indices
  : build_indices<N-1, N-1, Is...> {};

template <std::size_t... Is>
struct build_indices<0, Is...> : indices<Is...> {};
    
template< typename T, size_t N, size_t... Is>
constexpr array<T, N+1> push_back(array<T, N> const& arr, T const& val, indices<Is...>)
{
    // can only do single return statement in constexpr
    return {{arr.buf[Is]..., val}};
}
} // detail::

template < typename T, size_t Size >
constexpr array<T,Size+1> push_back(array<T,Size> const& arr, T const& val)
{
    return detail::push_back(arr, val, detail::build_indices<Size>{});
}

#include <iostream>

int main(){
    constexpr array<int, 3> v{{1, 2, 3}};
    constexpr array<int, 4> v2 = push_back(v, 4);
    constexpr array<int, v2.buf[3]+1> v3 = push_back(v2, 5);
    for(auto e : v3.buf)
      std::cout << e << " ";
}