#include <iostream>

namespace detail
{
    template <size_t N>
    size_t constexpr pack_size()
    { return N; }
    template <size_t N, typename T, typename... Ts>
    size_t constexpr pack_size()
    { return pack_size<N + 1, Ts...>(); }
}

template <typename... Ts>
size_t constexpr pack_size()
{ return detail::pack_size<0, Ts...>(); }

int main()
{ std::cout << pack_size<int, float, bool>() << std::endl; }
